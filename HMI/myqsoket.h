#ifndef MYQSOKET_H
#define MYQSOKET_H

#include <QObject>
#include <QtDebug>
#include <QString>
#include <QTcpSocket>


#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtGlobal>
#include <QTextStream>



class myQSoket : public QObject
{
    Q_OBJECT
public:
    explicit myQSoket(QObject *parent = nullptr);
    void doConnect();
    ~myQSoket();
private:
    QTcpSocket* myHMISoket;
    QByteArray* myQJosnByetedInPut;
signals:
    void dataIsRecived();
public slots:
};

#endif // MYQSOKET_H
