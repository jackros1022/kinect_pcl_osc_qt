
#include "kpoAppGui.h"

// QT4

// PCL
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>

#include <vtkRenderWindow.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
kpoAppGui::kpoAppGui (pcl::OpenNIGrabber& grabber)
    : vis_ ()
    , vis_timer_ (new QTimer (this))
    , kpoBaseApp(grabber)
//    , device_id_ ()
//    , scene_cloud_()
//    , depth_filter_ ()
    , ui_ (new Ui::KinectPclOsc)
{
    remove_noise_ = false;
    paused_ = false;
    estimate_normals_ = false;
    match_models_ = false;

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
    boost::function<void (const CloudConstPtr&)> f = boost::bind (&kpoAppGui::cloud_callback, this, _1);
    boost::signals2::connection c = grabber_.registerCallback (f);

    grabber_.start ();

    // Set defaults
    depth_filter_.setFilterFieldName ("z");
    depth_filter_.setFilterLimits (0.5, 5.0);


    connect (ui_->depthThresholdSlider, SIGNAL (valueChanged (int)), this, SLOT (adjustPassThroughValues (int)));

    modelListModel = new QStringListModel(this);
    QStringList list;

    modelListModel->setStringList(list);
    ui_->modelListView->setModel(modelListModel);

    grabber_downsampling_radius_ = .005f;

    m_sSettingsFile = QApplication::applicationDirPath() + "/settings.ini";

    std::cout <<  m_sSettingsFile.toStdString() << endl;
    loadSettings();

    connect (vis_timer_, SIGNAL (timeout ()), this, SLOT (timeoutSlot ()));
    vis_timer_->start (5);
}

void kpoAppGui::loadSettings()
{
    kpoBaseApp::loadSettings();

    if (ui_->depthThresholdSlider) {
        ui_->depthThresholdSlider->setValue(depthThreshold * 1000);
    }
}

void kpoAppGui::setDepthFromSliderValue(int depthThreshold)
{
    float scaledValue = float (depthThreshold) / 1000.0f;

    depth_filter_.setFilterLimits (0.0f, scaledValue);
    PCL_INFO ("Changed passthrough maximum value to: %f\n", scaledValue);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
void kpoAppGui::timeoutSlot ()
{
    if (!scene_cloud_ || paused_)
    {
        boost::this_thread::sleep (boost::posix_time::milliseconds (1));
        return;
    }

    updateView();
}


void kpoAppGui::updateView()
{
    {
        QMutexLocker locker (&mtx_);

        vis_->removePointCloud("scene_cloud_", 0);
        vis_->addPointCloud (scene_cloud_, "scene_cloud_");

        if (estimate_normals_ && scene_normals_) {
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

    kpoAppGui v (grabber);
    v.show ();
    return (app.exec ());
}


void kpoAppGui::adjustPassThroughValues (int new_value)
{
    setDepthFromSliderValue(new_value);
}

void kpoAppGui::on_pauseCheckBox_toggled(bool checked)
{
    paused_ = checked;
}


void kpoAppGui::on_computeNormalsCheckbox_toggled(bool checked)
{
    estimate_normals_ = checked;
    ui_->findSHOTdescriptors->setEnabled(checked);
}


void kpoAppGui::on_findSHOTdescriptors_toggled(bool checked)
{
    compute_descriptors_ = checked;
}

void kpoAppGui::pause()
{
    paused_ = true;
    ui_->pauseCheckBox->setChecked(true);
}


void kpoAppGui::on_saveDescriptorButton_clicked()
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

void kpoAppGui::saveDescriptors(string filename, const pcl::PointCloud<DescriptorType>::Ptr &descriptors)
{
    std::cout << "saving cloud with " << scene_cloud_->size() << " points" << std::endl;
    std::cout << "saving keypoints with " << scene_keypoints_->size() << " points" << std::endl;
    std::cout << "saving normals with " << scene_normals_->size() << " points" << std::endl;
    std::cout << "saving descriptors with " << scene_descriptors_->size() << " points" << std::endl;
    std::cout << "saving ref frames with " << scene_rf_->size() << " points" << std::endl;

    boost::shared_ptr<kpoObjectDescription> object_desc(new kpoObjectDescription(scene_cloud_, scene_keypoints_, scene_normals_, scene_descriptors_, scene_rf_));
    models_.push_back(object_desc);

    addStringToModelsList(filename);
}

void kpoAppGui::loadDescriptors(string filename)
{
    kpoBaseApp::loadDescriptors(filename);

    addStringToModelsList(filename);
}


void kpoAppGui::addStringToModelsList(string str)
{
    modelListModel->insertRow(modelListModel->rowCount());
    QModelIndex index = modelListModel->index(modelListModel->rowCount()-1);
    modelListModel->setData(index, QString(str.c_str()).section("/",-1,-1) );
}

void kpoAppGui::on_loadDescriptorButton_clicked()
{
    pause();

    QString filename = QFileDialog::getOpenFileName(this, tr("Load Descriptor"),
                                                    "",
                                                    tr("Files (*.descriptor.pcd)"));

    if (!filename.isEmpty()) {
        loadDescriptors(filename.toStdString());
    }
}



void kpoAppGui::on_matchModelsCheckbox_toggled(bool checked)
{
    match_models_ = checked;
}


void kpoAppGui::on_presampleRadiusSlider_valueChanged(int value)
{
    grabber_downsampling_radius_ = 0.1f / float(value);
}

void kpoAppGui::on_loadRawCloudButton_clicked()
{
    pause();

    QString filename = QFileDialog::getOpenFileName(this, tr("Load Raw Cloud"),
                                                    "",
                                                    tr("Files (*.pcd)"));

    if (!filename.isEmpty()) {

        CloudPtr cloud(new Cloud());

        pcl::PCDReader reader;
        reader.read<PointType> (filename.toStdString(), *cloud);

        process_cloud(cloud);
        updateView();
    }
}

void kpoAppGui::on_removeNoiseCheckBox_toggled(bool checked)
{
    remove_noise_ = checked;
}

void kpoAppGui::on_setOscTargetButton_clicked()
{
    int port = ui_->portTextInput->text().toInt();
    std::cout << "click" << std::endl;
    oscSender.setNetworkTarget(ui_->ipTextInput->text().toStdString().c_str(), port);
}



void kpoAppGui::on_depthThresholdlSlider_valueChanged(int value)
{
    setDepthFromSliderValue(value);
}

void kpoAppGui::on_downsamplingRadiusSlider_valueChanged(int value)
{
    float radius = float(value) / 10000.0f;

    pcl_functions_.setDownsamplingRadius(radius);
    ui_->downsamplingRadiusEdit->setText(QString::number(radius, 'g', 3));
}
