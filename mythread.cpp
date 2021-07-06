#include "mythread.h"
#include <QMetaType>
MyTHread::MyTHread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<cv::Mat>("cv::Mat&");
}

void MyTHread::videoThread(/*int deviceNo*/)
{
    //打开相机
    cv::VideoCapture Capture(0);
    if(!Capture.isOpened()) return;
    //循环
    while(1){
        if(flag_exitCamera==true) break;

        Capture>>this->frame;
        emit signal_frame(frame);
        QThread::msleep(1000/40);
    }

}
