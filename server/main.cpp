#include <QCoreApplication>
#include "mytcpserver.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    myTcpServer* server = new myTcpServer();

    return a.exec();
}
