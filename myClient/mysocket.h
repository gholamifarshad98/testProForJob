#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include<QDebug>
#include <QByteArray>
class mySocket : public QObject
{
    Q_OBJECT
public:
    explicit mySocket(QObject *parent = nullptr);
    void doConnect(quint16, QByteArray*);
    void writeMyJson();
    bool isConnected;
    ~mySocket();
private:
    QTcpSocket* myclientSoket;

signals:
    void connectionSignal( bool isConnected);
    void writenSignal(bool iswriten);
public slots:

};

#endif // MYSOCKET_H
