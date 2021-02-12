#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    w.showFullScreen();//全屏显示
    w.showMaximized();//最大化显示
//    w.show();
    return a.exec();
}
