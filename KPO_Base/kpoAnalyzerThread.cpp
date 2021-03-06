#include <QElapsedTimer>

#include "kpoAnalyzerThread.h"


kpoAnalyzerThread::kpoAnalyzerThread()
    : scene_cloud_ (new Cloud())
{
    downsampling_radius_ = .005f;
    shot_radius_ = 0.04f;

    cg_size_ = 0.01f;
    cg_thresh_ = 5.0f;

    rf_rad_ = 0.015f;
}

void kpoAnalyzerThread::setAnalyzerCallback(AnalyzerCallback callback)
{
    callback_ = callback;
}


void kpoAnalyzerThread::copyInputCloud(const Cloud &cloud, std::string filename_, unsigned object_id_)
{
    filename = filename_;
    object_id = object_id_;

    pcl::copyPointCloud(cloud, *scene_cloud_);
}

void kpoAnalyzerThread::operator ()()
{
    std::cout << "cloud has " << scene_cloud_->size() << " points" << std::endl;

    Cloud cleanCloud;
    removeNoise(scene_cloud_, cleanCloud);
    pcl::copyPointCloud(cleanCloud, *scene_cloud_);


    std::cout << "filtered cloud has " << scene_cloud_->size() << " points" << std::endl;
/*
    if (scene_cloud_->size() < 25) {
        std::cout << "cloud too small" << std::endl;
        return;
    }
/*
    if (scene_cloud_->size() > 40000) {
        std::cout << "cloud too large" << std::endl;
        return;
    }
*/
    NormalCloud::Ptr scene_normals_(new NormalCloud());
    estimateNormals(scene_cloud_, scene_normals_);

    Cloud::Ptr scene_keypoints_(new Cloud());
    downSample(scene_cloud_, scene_keypoints_);

    DescriptorCloud::Ptr scene_descriptors_(new DescriptorCloud());
    computeShotDescriptors(scene_cloud_, scene_keypoints_, scene_normals_, scene_descriptors_);

    RFCloud::Ptr scene_refs_(new RFCloud());
    estimateReferenceFrames(scene_cloud_, scene_normals_, scene_keypoints_, scene_refs_);

    kpoCloudDescription od;
    od.cloud = *scene_cloud_;
    od.keypoints = *scene_keypoints_;
    od.normals = *scene_normals_;
    od.descriptors = *scene_descriptors_;
    od.reference_frames = *scene_refs_;

    od.filename = filename;
    od.object_id = object_id;

    callback_(od);
}



void kpoAnalyzerThread::removeNoise(const CloudConstPtr &cloud, Cloud &filtered_cloud)
{
    pcl::StatisticalOutlierRemoval<PointType> statistical_outlier_remover;

    statistical_outlier_remover.setMeanK (50);
    statistical_outlier_remover.setStddevMulThresh (1.0);

    statistical_outlier_remover.setInputCloud (cloud);
    statistical_outlier_remover.filter (filtered_cloud);
}


void kpoAnalyzerThread::estimateNormals(const CloudConstPtr &cloud, NormalCloudPtr &normals)
{
    pcl::NormalEstimation<PointType, NormalType> norm_est;

    if (false) {
        norm_est.setKSearch (16);
    }
    else {
        pcl::search::KdTree<PointType>::Ptr tree (new pcl::search::KdTree<PointType> ());
        norm_est.setSearchMethod (tree);
        norm_est.setRadiusSearch (0.02);
    }
    norm_est.setInputCloud (cloud);
    norm_est.compute (*normals);
}


void kpoAnalyzerThread::downSample(const CloudConstPtr &cloud, CloudPtr &keypoints)
{
    pcl::UniformSampling<PointType> uniform_sampling;
    uniform_sampling.setRadiusSearch (downsampling_radius_);

    pcl::PointCloud<int> sampled_indices;

    uniform_sampling.setInputCloud (cloud);

    uniform_sampling.compute (sampled_indices);
    pcl::copyPointCloud (*cloud, sampled_indices.points, *keypoints);
}


void kpoAnalyzerThread::computeShotDescriptors(const CloudConstPtr &cloud, const CloudConstPtr &keypoints, const NormalCloud::ConstPtr &normals, DescriptorCloud::Ptr &descriptors)
{
    pcl::SHOTColorEstimation<PointType, NormalType, DescriptorType> shot;

    shot.setRadiusSearch (shot_radius_);

    shot.setInputCloud (keypoints);
    shot.setInputNormals (normals);
    shot.setSearchSurface (cloud);
    shot.compute (*descriptors);
}



void kpoAnalyzerThread::estimateReferenceFrames(const CloudConstPtr &cloud,
                             const NormalCloud::ConstPtr &normals,
                             const CloudConstPtr &keypoints,
                             RFCloud::Ptr &rf)
{
    pcl::BOARDLocalReferenceFrameEstimation<PointType, NormalType, RFType> rf_est;
    rf_est.setFindHoles (true);
    rf_est.setRadiusSearch (rf_rad_);

    if (!rf) {
        rf.reset(new RFCloud ());
    }

    rf_est.setInputCloud (keypoints);
    rf_est.setInputNormals (normals);
    rf_est.setSearchSurface (cloud);
    rf_est.compute (*rf);
}


double kpoAnalyzerThread::computeCloudResolution (const CloudConstPtr &cloud)
{
  double res = 0.0;
  int n_points = 0;
  int nres;
  std::vector<int> indices (2);
  std::vector<float> sqr_distances (2);
  pcl::search::KdTree<PointType> tree;
  tree.setInputCloud (cloud);

  for (size_t i = 0; i < cloud->size (); ++i)
  {
    if (! pcl_isfinite ((*cloud)[i].x))
    {
      continue;
    }
    //Considering the second neighbor since the first is the point itself.
    nres = tree.nearestKSearch (i, 2, indices, sqr_distances);
    if (nres == 2)
    {
      res += sqrt (sqr_distances[1]);
      ++n_points;
    }
  }
  if (n_points != 0)
  {
    res /= n_points;
  }
  return res;
}

