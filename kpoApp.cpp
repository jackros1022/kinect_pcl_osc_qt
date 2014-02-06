/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2009-2011, Willow Garage, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "kpoApp.h"
// QT4

// PCL
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>

#include <vtkRenderWindow.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KinectPclOsc::KinectPclOsc (pcl::OpenNIGrabber& grabber)
    : vis_ ()
    , grabber_(grabber)
    , device_id_ ()
    , scene_cloud_()
    , depth_filter_ ()
    , mtx_ ()
    , ui_ (new Ui::KinectPclOsc)
    , vis_timer_ (new QTimer (this))
{
    paused_ = false;
    show_normals_ = false;

    // Create a timer and fire it up every 5ms
    vis_timer_->start (5);

    connect (vis_timer_, SIGNAL (timeout ()), this, SLOT (timeoutSlot ()));

    ui_->setupUi (this);

    this->setWindowTitle ("Kinect > PCL > OSC");
    vis_.reset (new pcl::visualization::PCLVisualizer ("", false));
    vis_->resetCameraViewpoint ("scene_cloud_");

    vis_->setCameraPosition(0, 0, -1, //position
                            0, 0, 1, //view
                            0, -1, 0); // up

    ui_->qvtk_widget->SetRenderWindow (vis_->getRenderWindow ());
    vis_->setupInteractor (ui_->qvtk_widget->GetInteractor (), ui_->qvtk_widget->GetRenderWindow ());
    vis_->getInteractorStyle ()->setKeyboardModifier (pcl::visualization::INTERACTOR_KB_MOD_SHIFT);
    ui_->qvtk_widget->update ();

    // Start the OpenNI data acquision
    boost::function<void (const CloudConstPtr&)> f = boost::bind (&KinectPclOsc::cloud_callback, this, _1);
    boost::signals2::connection c = grabber_.registerCallback (f);

    grabber_.start ();

    // Set defaults
    depth_filter_.setFilterFieldName ("z");
    depth_filter_.setFilterLimits (0.5, 5.0);

    ui_->fieldValueSlider->setRange (5, 50);
    ui_->fieldValueSlider->setValue (50);

    connect (ui_->fieldValueSlider, SIGNAL (valueChanged (int)), this, SLOT (adjustPassThroughValues (int)));

    modelListModel = new QStringListModel(this);
    QStringList list;

    modelListModel->setStringList(list);
    ui_->modelListView->setModel(modelListModel);

    grabber_downsampling_radius_ = .005f;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
void KinectPclOsc::cloud_callback (const CloudConstPtr& cloud)
{
    if (paused_) return;

    QMutexLocker locker (&mtx_);
    //  FPS_CALC ("computation");

    // Computation goes here
    CloudPtr compressedCloud(new Cloud);

    pcl::PointCloud<int> sampled_indices;


    uniform_sampling.setInputCloud (cloud);
    uniform_sampling.setRadiusSearch (grabber_downsampling_radius_);

    uniform_sampling.compute (sampled_indices);
    pcl::copyPointCloud (*cloud, sampled_indices.points, *compressedCloud);


    scene_cloud_.reset (new Cloud);
    depth_filter_.setInputCloud (compressedCloud);
    depth_filter_.filter (*scene_cloud_);

    if (show_normals_) {

        scene_normals_.reset (new NormalCloud ());
        pcl_functions_.estimateNormals(scene_cloud_, scene_normals_);

        if (compute_descriptors_) {

            scene_keypoints_.reset(new Cloud ());
            pcl_functions_.downSample(scene_cloud_, scene_keypoints_);

            scene_descriptors_.reset(new DescriptorCloud ());
            pcl_functions_.computeShotDescriptors(scene_cloud_, scene_keypoints_, scene_normals_, scene_descriptors_);


//            double res = pcl_functions_.computeCloudResolution(scene_cloud_);
//            std::cout << "resolution = " << res << std::endl;

            scene_rf_.reset(new RFCloud ());
            pcl_functions_.estimateReferenceFrames(scene_cloud_, scene_normals_, scene_keypoints_, scene_rf_);


            if (match_models_) {

                pcl_functions_.setHoughSceneCloud(scene_keypoints_, scene_rf_);

                for (std::vector< boost::shared_ptr<kpoObjectDescription> >::iterator it = models_.begin(); it != models_.end(); ++it) {

                    pcl::CorrespondencesPtr model_scene_corrs (new pcl::Correspondences ());

                    pcl_functions_.correlateDescriptors(scene_descriptors_, (*it)->descriptors, model_scene_corrs);

//                    std::cout << "Correspondences found: " << model_scene_corrs->size () << std::endl;

                    std::vector<pcl::Correspondences> clustered;

                    clustered = pcl_functions_.houghCorrespondences((*it)->keypoints, (*it)->reference_frames, model_scene_corrs);

//                    std::cout << "number of clustered keypoints = " << clustered.size() << std::endl;

                    std::cout << clustered.size() << " ";
                }

                std::cout << std::endl;

            }
        }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void KinectPclOsc::timeoutSlot ()
{
    if (!scene_cloud_ || paused_)
    {
        boost::this_thread::sleep (boost::posix_time::milliseconds (1));
        return;
    }

    {
        QMutexLocker locker (&mtx_);

        vis_->removePointCloud("scene_cloud_", 0);
        vis_->addPointCloud (scene_cloud_, "scene_cloud_");

        if (show_normals_ && scene_normals_) {
            vis_->removePointCloud("normals", 0);
            vis_->addPointCloudNormals<PointType, NormalType> (scene_cloud_, scene_normals_, 100, .05, "normals");
            vis_->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_COLOR, 1.0, 1.0, 0.0, "normals");
        }

        if (compute_descriptors_ && scene_keypoints_) {
            vis_->removePointCloud("scene_keypoints", 0);
            pcl::visualization::PointCloudColorHandlerCustom<PointType> scene_keypoints_color_handler (scene_keypoints_, 0, 0, 255);
            vis_->addPointCloud (scene_keypoints_, scene_keypoints_color_handler, "scene_keypoints");
            vis_->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "scene_keypoints");
        }
    }
    //  FPS_CALC ("visualization");
    ui_->qvtk_widget->update ();
}



int main (int argc, char ** argv)
{
    // Initialize QT
    QApplication app (argc, argv);

    // Open the first available camera
    pcl::OpenNIGrabber grabber ("#1");
    // Check if an RGB stream is provided
    if (!grabber.providesCallback<pcl::OpenNIGrabber::sig_cb_openni_point_cloud> ())
    {
        PCL_ERROR ("Device #1 does not provide an RGB stream!\n");
        return (-1);
    }

    KinectPclOsc v (grabber);
    v.show ();
    return (app.exec ());
}


void KinectPclOsc::adjustPassThroughValues (int new_value)
{
    depth_filter_.setFilterLimits (0.0f, float (new_value) / 10.0f);
    PCL_INFO ("Changed passthrough maximum value to: %f\n", float (new_value) / 10.0f);
}

void KinectPclOsc::on_pauseCheckBox_toggled(bool checked)
{
    paused_ = checked;
}


void KinectPclOsc::on_computeNormalsCheckbox_toggled(bool checked)
{
    show_normals_ = checked;
    ui_->findSHOTdescriptors->setEnabled(checked);
    if (show_normals_) {

    }
    else {

    }
}


void KinectPclOsc::on_findSHOTdescriptors_toggled(bool checked)
{
    compute_descriptors_ = checked;
}

void KinectPclOsc::pause()
{
    paused_ = true;
    ui_->pauseCheckBox->setChecked(true);
}


void KinectPclOsc::on_saveDescriptorButton_clicked()
{
    pause();

    std::string objectname =  ui_->objectNameTextInput->text().toStdString();

    std::cout << "will save object " << objectname << std::endl;

    std::replace( objectname.begin(), objectname.end(), ' ', '_');

    QString defaultFilename = QString::fromUtf8(objectname.c_str()) + QString(".descriptor.pcd");

    QString filename = QFileDialog::getSaveFileName(this, tr("Save Descriptor"),
                                                    defaultFilename,
                                                    tr("Descriptors (*.dsc)"));

    if (!filename.isEmpty()) {
        saveDescriptors(filename.toStdString(), scene_descriptors_);
    }
}

void KinectPclOsc::saveDescriptors(string filename, const pcl::PointCloud<DescriptorType>::Ptr &descriptors)
{
    /*
    pcl::PCDWriter writer;
    writer.write<DescriptorType> (filename, *scene_descriptors_, false);
    */

    std::cout << "saving cloud with " << scene_cloud_->size() << " points" << std::endl;
    std::cout << "saving keypoints with " << scene_keypoints_->size() << " points" << std::endl;
    std::cout << "saving normals with " << scene_normals_->size() << " points" << std::endl;
    std::cout << "saving descriptors with " << scene_descriptors_->size() << " points" << std::endl;
    std::cout << "saving ref frames with " << scene_rf_->size() << " points" << std::endl;

    boost::shared_ptr<kpoObjectDescription> object_desc(new kpoObjectDescription(scene_cloud_, scene_keypoints_, scene_normals_, scene_descriptors_, scene_rf_));
    models_.push_back(object_desc);

    addStringToModelsList(filename);
}

void KinectPclOsc::addStringToModelsList(string str)
{
    modelListModel->insertRow(modelListModel->rowCount());
    QModelIndex index = modelListModel->index(modelListModel->rowCount()-1);
    modelListModel->setData(index, QString(str.c_str()).section("/",-1,-1) );
}

void KinectPclOsc::on_loadDescriptorButton_clicked()
{
    pause();

    QString filename = QFileDialog::getOpenFileName(this, tr("Load Descriptor"),
                                                    "",
                                                    tr("Files (*.descriptor.pcd)"));

    if (!filename.isEmpty()) {
        loadDescriptors(filename.toStdString());
    }
}

void KinectPclOsc::loadDescriptors(string filename)
{
    pcl::PointCloud<DescriptorType>::Ptr model_descriptors_(new pcl::PointCloud<DescriptorType>());

    pcl::PCDReader reader;
    reader.read<DescriptorType> (filename, *model_descriptors_);

    //    models_.push_back(model_descriptors_);
    addStringToModelsList(filename);
}


void KinectPclOsc::on_matchModelsCheckbox_toggled(bool checked)
{
    match_models_ = checked;
}


void KinectPclOsc::on_presampleRadiusSlider_valueChanged(int value)
{
    grabber_downsampling_radius_ = 0.1f / float(value);
}
