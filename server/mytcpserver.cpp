#include "mytcpserver.h"

myTcpServer::myTcpServer(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);
    myQJosnByetedInPut= new QByteArray();
    myQJosnByetedOutPut= new QByteArray();
    connect(myServer,SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!myServer->listen(QHostAddress::Any, 8585))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void myTcpServer::prepareOutPut()
{
    QFile fin("recivedDataFromServer.json");
    fin.open(QIODevice::ReadOnly);
    QString readJsonFile = fin.readAll();
    fin.close();
    QJsonDocument readJsonFileDoc = QJsonDocument::fromJson(readJsonFile.toUtf8());
    QJsonObject readJsonObj = readJsonFileDoc.object();
    int Switch_1_status = 0;
    int Switch_2_status = 0;
    int Switch_3_status = 0;
    int Switch_4_status = 0;
    if(readJsonObj.value("Switch_1").toVariant().value<bool>()==true){
        Switch_1_status=1;
    }
    if(readJsonObj.value("Switch_2").toVariant().value<bool>()==true){
        Switch_2_status=1;
    }
    if(readJsonObj.value("Switch_3").toVariant().value<bool>()==true){
        Switch_3_status=1;
    }
    if(readJsonObj.value("Switch_4").toVariant().value<bool>()==true){
        Switch_4_status=1;
    }
    double outPut1= Switch_1_status*1500.48+Switch_2_status*1500+Switch_3_status*250+45;
    double outPut2= Switch_2_status*1500.47+Switch_3_status*1400+23;
    double outPut3= Switch_4_status*900.51+Switch_3_status*1400+12;
    readJsonObj["outPut1"]=outPut1;
    readJsonObj["outPut2"]=outPut2;
    readJsonObj["outPut3"]=outPut3;
    *myQJosnByetedOutPut = QJsonDocument(readJsonObj).toJson();
    QFile outPutFile("serverOutPut.json");
    outPutFile.open(QIODevice::WriteOnly);
    outPutFile.write(*myQJosnByetedOutPut);
    outPutFile.close();
}

myTcpServer::~myTcpServer()
{
    delete myServer;
    delete myQJosnByetedInPut;
    delete myQJosnByetedOutPut;

}

void myTcpServer::newConnection()
{
    QTcpSocket* myServerSocket= myServer->nextPendingConnection();
    myServerSocket->waitForReadyRead(30000);
    *myQJosnByetedInPut = myServerSocket->readAll();

    QString str("Im HMI");
    QByteArray bytes = str.toLatin1();
    if(*myQJosnByetedInPut ==bytes ){
        prepareOutPut();
        myServerSocket->write(*myQJosnByetedOutPut);
        myServerSocket->flush();
        myServerSocket->waitForBytesWritten(3000);
    }else {
        QFile fin("recivedDataFromServer.json");
        fin.open(QIODevice::WriteOnly);
        fin.write(*myQJosnByetedInPut);
}

    myServerSocket->close();

}
