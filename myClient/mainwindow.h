#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtGlobal>
#include <QTextStream>

#include <mysocket.h>




#include <QMainWindow>
#include <QString>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QByteArray* returningJson;
    mySocket* socket;
    quint16 PortNumber;
private slots:
    void reportConnectionStatus(bool);
    void reportSendingStatus(bool);

    void on_switch_1_toggled(bool checked);
    void on_switch_2_toggled(bool checked);
    void on_switch_3_toggled(bool checked);
    void on_switch_4_toggled(bool checked);

    void on_pushButtonSetPort_clicked();

private:
    Ui::MainWindow *ui;
    QString* portNumber_s;


    bool* switchStat1;
    bool* switchStat2;
    bool* switchStat3;
    bool* switchStat4;

    void prepareQJson();


};

#endif // MAINWINDOW_H
