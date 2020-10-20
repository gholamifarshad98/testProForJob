#include "mysocket.h"

mySocket::mySocket(QObject *parent) : QObject(parent)
{
    myclientSoket= new QTcpSocket(this) ;
}

void mySocket::doConnect(quint16 _portNumber, QByteArray* _data)
{

    myclientSoket->connectToHost("127.0.0.1",_portNumber);

   if(myclientSoket->waitForConnected(1000)){
       isConnected =true;
       emit connectionSignal(isConnected);
       myclientSoket->write(*_data);
       if(myclientSoket->waitForBytesWritten(1000)){
        emit writenSignal(true);
       }else {
        emit writenSignal(false);
       }
   }else {
       isConnected =false;
       emit connectionSignal(isConnected);
   }
}

mySocket::~mySocket()
{
    delete myclientSoket;
}
