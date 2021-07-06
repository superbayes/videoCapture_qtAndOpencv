#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "mythread.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    cv::Mat frame;
    QImage frame2QImage;
    MyTHread *videoThread;
    QThread *thread;

public:
    QImage Mat2QImage(const cv::Mat& InputMat);
signals:
    void signal_openVideo();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
