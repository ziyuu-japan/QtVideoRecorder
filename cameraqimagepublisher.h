#ifndef CAMERAQIMAGEPUBLISHER_H
#define CAMERAQIMAGEPUBLISHER_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include "opencv2/opencv.hpp"

class CameraQImagePublisher : public QObject
{
    Q_OBJECT
public:
    explicit CameraQImagePublisher(QObject *parent = nullptr);

    ~CameraQImagePublisher();
    void process();
    QImage getCameraQImage();

signals:
    void finished();
    void publishQImage(QImage);
};

#endif // CAMERAQIMAGEPUBLISHER_H
