#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new QThread();
    videoThread = new MyTHread();
    videoThread->moveToThread(thread);

    connect(ui->pB_open,&QPushButton::clicked,this,[&](){
        thread->start();
        emit signal_openVideo(0);
    });
    connect(this,&MainWindow::signal_openVideo,videoThread,&MyTHread::videoThread);
    connect(videoThread,&MyTHread::signal_frame,this,[&](cv::Mat& frame){
        this->frame = frame;
        this->frame2QImage = this->Mat2QImage(frame);
        ui->label->setPixmap(QPixmap::fromImage(frame2QImage));
        qDebug()<<"视频帧=="<<frame.rows<<frame.cols;
    });


    connect(this,&MainWindow::destroyed,[&](){
        videoThread->flag_exitCamera = true;
        thread->quit();
        thread->wait();
        qDebug()<<"关闭线程====";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::Mat2QImage(const cv::Mat &InputMat)
{
    cv::Mat TmpMat;
    QImage Result;
    // convert the color space to RGB
    if (InputMat.channels() == 1)
    {
        cv::cvtColor(InputMat,TmpMat,cv::COLOR_GRAY2RGB);
        Result=QImage((const uchar*)(TmpMat.data), TmpMat.cols, TmpMat.rows,TmpMat.cols*TmpMat.channels(),
                      QImage::Format_Indexed8);

    }
    else
    {

        cv::cvtColor(InputMat, TmpMat, cv::COLOR_BGR2RGB);
        // construct the QImage using the data of the mat, while do not copy the data
        Result = QImage((const uchar*)(TmpMat.data), TmpMat.cols, TmpMat.rows,TmpMat.cols*TmpMat.channels(),
                               QImage::Format_RGB888);
    }

    // deep copy the data from mat to QImage
    Result.bits();
    return Result;
}


void MainWindow::on_pB_configCamera_clicked()
{
    qDebug()<<"启相机参数自调节模式";
    if(thread->isRunning()){
        videoThread->Capture.set(cv::CAP_PROP_SETTINGS, 1);//开启相机参数自调节模式
    }
}

void MainWindow::on_actioncamera_config_triggered()
{
    qDebug()<<"启相机参数自调节模式";
//    if(thread->isRunning()){
//        videoThread->Capture.set(cv::CAP_PROP_SETTINGS, 1);//开启相机参数自调节模式
//    }
}
