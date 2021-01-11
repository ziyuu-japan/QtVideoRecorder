#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      saved_image_path_("")
{
    connect(this, &MainWindow::publishQImage,
            this, &MainWindow::onQImageSubscribed);
    initializeCentralWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1200, 900);
}


void MainWindow::initializeCentralWidget()
{
    QWidget *widget = new QWidget(this);

    layout_ = new QVBoxLayout(widget);
    start_camera_button_ = new QPushButton("Start Camera");
    camera_viewer_ = new QGraphicsView();
    graphics_scene_ = new QGraphicsScene();
    graphics_pixmap_item_ = new QGraphicsPixmapItem();
    graphics_scene_->addItem(graphics_pixmap_item_);
    camera_viewer_->setScene(graphics_scene_);
    create_time_lapse_button_ = new QPushButton("Create Time Lapse");
    connect(create_time_lapse_button_, &QPushButton::clicked,
            this, &MainWindow::onCreateTimelapseButtonClicked);

    layout_->addWidget(start_camera_button_);
    layout_->addWidget(camera_viewer_);
    layout_->addWidget(create_time_lapse_button_);

    widget->setLayout(layout_);

    start_camera_button_connection_ = \
            connect(start_camera_button_, &QPushButton::clicked,
                    this, &MainWindow::onStartCameraButtonPushed);

    setCentralWidget(widget);
}

// ボタンを押したらカメラ起動、ファイルも保存、あるボタンでffmpeg実行、動画生成
void MainWindow::onStartCameraButtonPushed() {
    qDebug() << "start camera button pushed.";
    disconnect(start_camera_button_);
    start_camera_button_->setEnabled(false);



    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::cameraQImageSender);
    timer->start(1000);
}

void MainWindow::cameraQImageSender(){
    qDebug("Worker run");
    qDebug("QImage was published.");

    emit publishQImage(getCameraQImage());
}

QImage MainWindow::getCameraQImage() {
    cap_ptr_.reset(new cv::VideoCapture);
    qDebug() << "reset called.";
    if(cap_ptr_->isOpened()){
        qDebug() << "Camera is already opened.";
    } else {
        if(!cap_ptr_->open(0)){
            qDebug() << "Failed to open camera.";
            return QImage();
        } else {
            qDebug() << "Success to openc camera.";
        }
    }

    cv::Mat src, dst;
    cap_ptr_->grab();
    cap_ptr_->retrieve(src);
    qDebug() << "executed.";

    //cv::cvtColor(src, dst, CV_RGB2BGR);
    cv::cvtColor(src, dst, CV_BGR2RGB);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string saved_image_path ="savedImage/";
    std::string timestamp = "";
    timestamp.append(std::to_string(1900 + ltm->tm_year));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_mon + 1));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_mday));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_hour));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_min));
    timestamp.append(".jpg");
    saved_image_path.append(timestamp);

    if(saved_image_path_ == "" || saved_image_path_ != saved_image_path){
        cv::imwrite(saved_image_path, dst);

    }
    saved_image_path_ = saved_image_path;

    QImage qimage((uchar *)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888);

    return qimage;
}

void MainWindow::onQImageSubscribed(QImage qimage)
{
    qDebug() << "onQImageSubscribed() called.";
  graphics_pixmap_item_->setPixmap(QPixmap::fromImage(qimage));
}

void MainWindow::onCreateTimelapseButtonClicked(){
    qDebug() << "nCreateTimelapseButtonClicked() called.";

    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string saved_image_path ="savedImage/";
    std::string timestamp = "";
    timestamp.append(std::to_string(1900 + ltm->tm_year));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_mon + 1));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_mday));
    timestamp.append("_");
    timestamp.append(std::to_string(ltm->tm_hour));
    timestamp.append("_");
    timestamp.append("%d");
    timestamp.append(".jpg");
    saved_image_path.append(timestamp);
    std::string generate_timelapse_command_string;
    generate_timelapse_command_string = "ffmpeg -f image2 -r 15 -i ";
    generate_timelapse_command_string.append(saved_image_path);
    generate_timelapse_command_string.append(" -r 15 -an -vcodec libx264 -pix_fmt yuv420p video.mp4");
    qDebug() << generate_timelapse_command_string.c_str();
    system(generate_timelapse_command_string.c_str());
}
