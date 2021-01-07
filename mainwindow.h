#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "opencv2/opencv.hpp"
#include <mutex>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSize sizeHint() const;
    void initializeCentralWidget();
    void onStartCameraButtonPushed();
    void cameraQImageSender();
    QImage getCameraQImage();
private:
    Ui::MainWindow *ui;

    QMetaObject::Connection start_camera_button_connection_;
    QVBoxLayout *layout_;
    QPushButton *start_camera_button_;
    QGraphicsView *camera_viewer_;
    QGraphicsScene *graphics_scene_;
    QPushButton *create_time_lapse_button_;

    QThread *thread_;

    std::mutex mutex_;

    std::string saved_image_path_;

    std::unique_ptr<cv::VideoCapture> cap_ptr_;
signals:
    void threadFinished();
    void publishQImage(QImage);
private slots:
    void onQImageSubscribed(QImage);
    void onCreateTimelapseButtonClicked();
};
#endif // MAINWINDOW_H
