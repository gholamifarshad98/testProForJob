#include "mythread.h"

void MyThread::run()
{
    while (true) {
         socket->doConnect();
    }


}

MyThread::MyThread()
{
socket = new myQSoket();
connect(socket,SIGNAL(dataIsRecived), this , SLOT(readyToShow));
}

MyThread::~MyThread()
{
    delete socket;
}
