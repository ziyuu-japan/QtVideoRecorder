#include "graphicsscene.h"
#include <QGraphicsPixmapItem>
#include "opencv2/opencv.hpp"
#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent): QGraphicsScene(parent), m_isDrag(false)
{
    //addItem(new QGraphicsPixmapItem(QPixmap(":/images/campus_map.png")));
    addIcon(*(new QPointF(0, 0)));
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_isDrag = false;
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
    m_isDrag = true;
}

void GraphicsScene::onQImageSubscribed(QImage qimage)
{
    qDebug() << "QImage was subscribed";
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(qimage)));
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);

    if(!m_isDrag){
        addIcon(*(new QPointF(0, 0)));
    }
}

void GraphicsScene::addIcon(const QPointF pos)
{
    //    cv::VideoCapture cap;
    //    cap.open(0);
    //    for(;;)
    //    {
    //          cv::Mat frame;
    //          cap >> frame;
    //          if( frame.empty() ) break; // end of video stream
    //          imshow("this is you, smile! :)", frame);
    //          if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    //    }

    //    cv::VideoCapture cap;
    //    cap.open(0);
    //    for(;;)
    //    {
    //          cv::Mat frame;
    //          cap >> frame;
    //          if( frame.empty() ) break; // end of video stream
    //          imshow("this is you, smile! :)", frame);
    //          if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    //    }
    // Renew camera image
//    cv::VideoCapture cap;
//    cap.open(0);
//    cv::Mat src, dst;
//    cap >> src;
//    qDebug() << "executed.";

      // cv::Mat -> QImage

//          cv::cvtColor(src, dst, CV_RGB2BGR);
//          QImage tmp((uchar *)dst.data, dst.cols, dst.rows,
//                             dst.step, QImage::Format_RGB888);
//    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(tmp)));
}
