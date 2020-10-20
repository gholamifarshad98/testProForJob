#include "mainwindow.h"
#include <QApplication>
#include<mythread.h>
#include <QObject>
#include<QByteArray>
#include<QEvent>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyThread* thread = new MyThread();
    MainWindow w;
    thread->start();
    w.show();
    while (true) {
        QCoreApplication::processEvents();
        w.checkData();
    }
    return 0;//a.exec();
}
