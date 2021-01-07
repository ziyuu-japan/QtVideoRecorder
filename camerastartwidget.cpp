#include "camerastartwidget.h"


#include <QThread>

CameraStartWidget::CameraStartWidget(QWidget *parent) : QWidget(parent)
{
    m_threadButton = new QPushButton("Thread start", this);
    m_connection = connect(m_threadButton, &QPushButton::clicked,
                            this, &CameraStartWidget::startThread);
}



CameraStartWidget::~CameraStartWidget(){

}

QSize CameraStartWidget::sizeHint() const{
    return QSize(400, 300);
}

void CameraStartWidget::startThread(bool b) {

    //  最初にボタンを押したときだけスレッドを立てる
    disconnect(m_connection);
    m_threadButton->setEnabled(false);

    m_thread = new QThread();
    camera_qimage_publisher = new CameraQImagePublisher();
    camera_qimage_publisher->moveToThread(m_thread);



    connect(m_thread, &QThread::started, camera_qimage_publisher, &CameraQImagePublisher::process);

    //  終了時メモリクリア
    connect(camera_qimage_publisher, &CameraQImagePublisher::finished, m_thread, &QThread::quit);
    connect(camera_qimage_publisher, &CameraQImagePublisher::finished, camera_qimage_publisher, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, m_thread, &CameraQImagePublisher::deleteLater);

    m_thread->start();
}
