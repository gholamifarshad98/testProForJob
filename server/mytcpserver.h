#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QDebug>
#include <QTcpServer>
#include<QTcpSocket>
#include <QObject>





#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtGlobal>
#include <QTextStream>



class myTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit myTcpServer(QObject *parent = nullptr);
private:
    QTcpServer* myServer;
    QByteArray* myQJosnByetedInPut;
    QByteArray* myQJosnByetedOutPut;
    void prepareOutPut();
    ~myTcpServer();

signals:

public slots:
    void newConnection();
};

#endif // MYTCPSERVER_H
