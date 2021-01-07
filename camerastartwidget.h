#ifndef CAMERASTARTWIDGET_H
#define CAMERASTARTWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "cameraqimagepublisher.h"

class CameraStartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraStartWidget(QWidget *parent = nullptr);
    ~CameraStartWidget();
    QSize sizeHint() const override;
    CameraQImagePublisher *camera_qimage_publisher;
private slots:

    void startThread(bool b);
signals:

private:
    QThread *m_thread;
    QPushButton *m_threadButton;
    QPushButton *m_btnSignal;
    QMetaObject::Connection m_connection;

};

#endif // CAMERASTARTWIDGET_H
