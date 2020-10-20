#include "myqsoket.h"
#include <QThread>
myQSoket::myQSoket(QObject *parent) : QObject(parent)
{
    myHMISoket = new QTcpSocket(this);
    myQJosnByetedInPut= new QByteArray();

}

void myQSoket::doConnect()
{
    myHMISoket->connectToHost("127.0.0.1",8585);
   if(myHMISoket->waitForConnected(50000)){
       myHMISoket->write("Im HMI");
       myHMISoket->flush();
       myHMISoket->waitForBytesWritten(50000);
       myHMISoket->waitForReadyRead(30000);
       *myQJosnByetedInPut = myHMISoket->readAll();
       qDebug()<<*myQJosnByetedInPut;
       QString newData= *myQJosnByetedInPut;
       QJsonDocument newReadJsonFileDoc = QJsonDocument::fromJson(newData.toUtf8());
       QJsonObject newReadJsonObj = newReadJsonFileDoc.object();
       bool mustUpdat= false;
       if(newReadJsonObj.value("outPut1").toVariant().value<double>()>0){

           mustUpdat= true;
       }

       if(*myQJosnByetedInPut->data() & mustUpdat){
           mustUpdat= false;
           QFile fin("recivedDataFromHMI.json");
           fin.open(QIODevice::WriteOnly);
           fin.write(*myQJosnByetedInPut);
           fin.close();

       }
   }

}

myQSoket::~myQSoket()
{
    delete myHMISoket;
    delete myQJosnByetedInPut;
}
