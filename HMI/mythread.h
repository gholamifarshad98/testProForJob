#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <myqsoket.h>
class MyThread : public QThread
{
public:
    void run();
    MyThread();
    ~MyThread();
    myQSoket *socket;
public slots:
    void readyToShow();
signals:
    void emitToGUI();

};

#endif // MYTHREAD_H
