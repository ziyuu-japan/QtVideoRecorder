#include "widget.h"
#include "ui_form.h"

#include <QDebug>
#include <camerastartwidget.h>
#include <cameraqimagepublisher.h>
#include <QThread>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    //QGraphicsScene?QGraphicsView?????.
    QThread *m_thread;
    CameraQImagePublisher *camera_qimage_publisher;
    m_thread = new QThread();
    camera_qimage_publisher = new CameraQImagePublisher();
    camera_qimage_publisher->moveToThread(m_thread);
    connect(m_thread, &QThread::started, camera_qimage_publisher, &CameraQImagePublisher::process);
    m_thread->start();
    qDebug() << m_thread->isRunning();
    connect(camera_qimage_publisher, &CameraQImagePublisher::publishQImage,
            &m_scene, &GraphicsScene::onQImageSubscribed);
    m_scene_ptr = &m_scene;
    ui->graphicsView->setScene(m_scene_ptr);
    qDebug() << "ui->graphicsView->rect()" << ui->graphicsView->rect();
    //QGraphicsScene????QGraphicsView?????.
    //m_scene.setSceneRect(ui->graphicsView->rect());
    //qDebug() << "m_scene.sceneRect()" << m_scene.sceneRect();
}

Widget::~Widget()
{

}
