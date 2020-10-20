#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myqsoket.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    directory= QDir::current();
    sefidPath=directory.filePath("sefid.png");
    redPath=directory.filePath("redSwitch.png");
    bluePath=directory.filePath("blueSwitch.png");
    backgroundPath=directory.filePath("background.png");

    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(backgroundPath));
    ui->lcdNumberkV->setDecMode();
    ui->lcdNumberMW->setDecMode();
    ui->lcdNumberMVA->setDecMode();
    ui->lcdNumberMW->setPalette(Qt::black);
    ui->lcdNumberkV->setPalette(Qt::black);
    ui->lcdNumberMVA->setPalette(Qt::black);
    sw_1_pre=false;
    sw_2_pre=false;
    sw_3_pre=false;
    sw_4_pre=false;
    outPut1_pre=0;
    outPut2_pre=0;
    outPut3_pre=0;

    sw_1=false;
    sw_2=false;
    sw_3=false;
    sw_4=false;
    outPut1=0;
    outPut2=0;
    outPut3=0;

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkData()
{
    QFile fin("recivedDataFromHMI.json");
    fin.open(QIODevice::ReadOnly);
    QString readJsonFile = fin.readAll();
    fin.close();
    QJsonDocument readJsonFileDoc = QJsonDocument::fromJson(readJsonFile.toUtf8());
    QJsonObject readJsonObj = readJsonFileDoc.object();
    sw_1=readJsonObj.value("Switch_1").toVariant().value<bool>();
    sw_2=readJsonObj.value("Switch_2").toVariant().value<bool>();
    sw_3=readJsonObj.value("Switch_3").toVariant().value<bool>();
    sw_4=readJsonObj.value("Switch_4").toVariant().value<bool>();
    outPut1=readJsonObj.value("outPut1").toVariant().value<double>();
    outPut2=readJsonObj.value("outPut2").toVariant().value<double>();
    outPut3=readJsonObj.value("outPut3").toVariant().value<double>();
    if((sw_1!=sw_1_pre || sw_2!=sw_2_pre || sw_3!=sw_3_pre || sw_4!=sw_4_pre || outPut1!=outPut1_pre || outPut2!=outPut2_pre || outPut3!=outPut3_pre) & !(outPut1==0 & outPut2==0 & outPut1==0)){
        setData();
        sw_1_pre=sw_1;
        sw_2_pre=sw_2;
        sw_3_pre=sw_3;
        sw_4_pre=sw_4;
        outPut1_pre=outPut1;
        outPut2_pre=outPut2;
        outPut3_pre=outPut3;
    }
}


void MainWindow::setData()
{

    if(sw_1){
        ui->label_SW1 ->setPixmap(QPixmap(redPath));
    }else {
        ui->label_SW1 ->setPixmap(QPixmap(sefidPath));
    }
    if(sw_2){
        ui->label_SW2 ->setPixmap(QPixmap(redPath));
    }else {
        ui->label_SW2 ->setPixmap(QPixmap(sefidPath));
    }
    if(sw_3){
        ui->label_SW3 ->setPixmap(QPixmap(redPath));
    }else {
        ui->label_SW3 ->setPixmap(QPixmap(sefidPath));
    }
    if(sw_4){
        ui->label_SW4 ->setPixmap(QPixmap(bluePath));
    }else {
        ui->label_SW4 ->setPixmap(QPixmap(sefidPath));
    }


    ui->lcdNumberkV->display(outPut1);
    ui->lcdNumberMW->display(outPut2);
    ui->lcdNumberMVA->display(outPut3);




}
