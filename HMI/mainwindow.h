#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void checkData();
    void setData();
    bool sw_1_pre;
    bool sw_2_pre;
    bool sw_3_pre;
    bool sw_4_pre;
    double outPut1_pre;
    double outPut2_pre;
    double outPut3_pre;

    bool sw_1;
    bool sw_2;
    bool sw_3;
    bool sw_4;
    double outPut1;
    double outPut2;
    double outPut3;
    QDir directory;
    QString sefidPath;
    QString redPath;
    QString bluePath;
    QString backgroundPath;



private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
