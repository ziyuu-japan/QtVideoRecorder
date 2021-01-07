#include "cameraqimagepublisher.h"



CameraQImagePublisher::CameraQImagePublisher(QObject *parent) : QObject(parent)
{

}

CameraQImagePublisher::~CameraQImagePublisher() {
    qDebug() << __FUNCTION__;
}

void CameraQImagePublisher::process() {
    qDebug("Worker run");
    qDebug("QImage was published.");

    while(1){
    emit publishQImage(getCameraQImage());

    }
}

QImage CameraQImagePublisher::getCameraQImage() {
    cv::VideoCapture cap;
    if(!cap.open(0)){
        qDebug() << "Failed to open camera.";
        return QImage();
    } else {
        qDebug() << "Success to openc camera.";
    }
    cv::Mat src, dst;
    cap >> src;
    qDebug() << "executed.";

    cv::cvtColor(src, dst, CV_RGB2BGR);
    QImage qimage((uchar *)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888);

    return qimage;
}
