#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   PortNumber=0;
   returningJson = new QByteArray();
   switchStat1 = new bool(false);
   switchStat2 = new bool(false);
   switchStat3 = new bool(false);
   switchStat4 = new bool(false);
   ui->setupUi(this);
   ui->lineEditPortNumber->setValidator( new QIntValidator(0, 99999, this) );
   ui->textEditReporter->setTextColor( QColor( "red" ) );
   ui->textEditReporter->append("At First you must set Port number.");
   ui->textEditReporter->setTextColor( QColor( "black" ) );
   socket = new mySocket(this);
   connect(socket, SIGNAL(connectionSignal(bool)), this, SLOT(reportConnectionStatus(bool)));
   connect(socket, SIGNAL(writenSignal(bool)), this, SLOT(reportSendingStatus(bool)));

}


MainWindow::~MainWindow()
{
    delete ui;
    delete returningJson  ;
    delete switchStat1   ;
    delete switchStat2   ;
    delete switchStat3   ;
    delete switchStat4   ;
    delete socket;
}

void MainWindow::reportConnectionStatus(bool _connectionStatus)
{
    if(_connectionStatus){
        ui->textEditReporter->setTextColor( QColor( "green" ) );
        ui->textEditReporter->append("The connection is successfully established.");
        ui->textEditReporter->setTextColor( QColor( "black" ) );
    }else {

        ui->textEditReporter->setTextColor( QColor( "red" ) );
        ui->textEditReporter->append("The connection is not successfully established.");
        ui->textEditReporter->setTextColor( QColor( "black" ) );
    }
}

void MainWindow::reportSendingStatus(bool _isWiten)
{
    if(_isWiten){
        ui->textEditReporter->setTextColor( QColor( "green" ) );
        ui->textEditReporter->append("The data is successfully written.");
        ui->textEditReporter->setTextColor( QColor( "black" ) );
    }else {

        ui->textEditReporter->setTextColor( QColor( "red" ) );
        ui->textEditReporter->append("The data is not successfully written.");
        ui->textEditReporter->setTextColor( QColor( "black" ) );
    }
}




void MainWindow::on_switch_1_toggled(bool checked)
{
    if(checked){
       *switchStat1 = true;
       ui->textEditReporter->append("Switch_1 satat is changed to \" Connected\". ");
    }else {
       *switchStat1=false;
       ui->textEditReporter->append("Switch_1 satat is changed to \" Disconnected\". ");
    }
    prepareQJson();
    socket->doConnect(PortNumber,returningJson);
}

void MainWindow::on_switch_2_toggled(bool checked)
{
    if(checked){
        *switchStat2 = true;
        ui->textEditReporter->append("Switch_2 satat is changed to \" Connected\". ");
    }else {
        *switchStat2=false;
        ui->textEditReporter->append("Switch_2 satat is changed to \" Disconnected\". ");
    }
    prepareQJson();
    socket->doConnect(PortNumber,returningJson);
}

void MainWindow::on_switch_3_toggled(bool checked)
{
    if(checked){
        *switchStat3 = true;
        ui->textEditReporter->append("Switch_3 satat is changed to \" Connected\". ");
    }else {
        *switchStat3=false;
        ui->textEditReporter->append("Switch_3 satat is changed to \" Disconnected\". ");
    }
    prepareQJson();
    socket->doConnect(PortNumber,returningJson);
}

void MainWindow::on_switch_4_toggled(bool checked)
{

    if(checked){
        *switchStat4 = true;
        ui->textEditReporter->append("Switch_4 satat is changed to \" Connected\". ");
    }else {
        *switchStat4=false;
        ui->textEditReporter->append("Switch_4 satat is changed to \" Disconnected\". ");
    }
    prepareQJson();
    socket->doConnect(PortNumber,returningJson);
}


void MainWindow::on_pushButtonSetPort_clicked()
{
    QString report = "Connecting o port "+ ui->lineEditPortNumber->text();
    PortNumber =  ui->lineEditPortNumber->text().QString::toUShort();
    ui->textEditReporter->append(report);
    prepareQJson();
    socket->doConnect(PortNumber,returningJson);


}

void MainWindow::prepareQJson()
{
    QJsonObject root;
    root["Switch_1"] = (*switchStat1);
    root["Switch_2"] = (*switchStat2);
    root["Switch_3"] = (*switchStat3);
    root["Switch_4"] = (*switchStat4);
    *returningJson= QJsonDocument(root).toJson();
    QFile outPutFile("clientSwitchsState.json");
    outPutFile.open(QIODevice::WriteOnly);
    outPutFile.write(*returningJson);
}
