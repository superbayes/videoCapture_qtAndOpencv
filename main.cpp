#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    cv::Mat src(800,500,CV_8UC3,cv::Scalar(255,0,0));
//    cv::imshow("src",src);
    MainWindow w;
    w.show();
    return a.exec();
}
