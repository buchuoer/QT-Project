#ifndef CHANGE_BACK_H
#define CHANGE_BACK_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class change_back;
}

class change_back : public QWidget
{
    Q_OBJECT

public:
    change_back(my_tcpsocket *tcp, int userId, QWidget *parent = nullptr);
    ~change_back();
    void Show(){
        changebgw->show();
    }

private slots:
    void Background1Clicked();
    void Background2Clicked();
    void Background3Clicked();
    void Background4Clicked();
    void Background5Clicked();
    void Background6Clicked();
    void Background7Clicked();
    void Background8Clicked();
    void Background9Clicked();
    void Background10Clicked();
    void Background11Clicked();
    void Background12Clicked();
    void Background13Clicked();
    void Background14Clicked();
    void Background15Clicked();
    void Background16Clicked();

private:
    QPushButton* bg1 = new QPushButton;
    QPushButton* bg2 = new QPushButton;
    QPushButton* bg3 = new QPushButton;
    QPushButton* bg4 = new QPushButton;
    QPushButton* bg5 = new QPushButton;
    QPushButton* bg6 = new QPushButton;
    QPushButton* bg7 = new QPushButton;
    QPushButton* bg8 = new QPushButton;
    QPushButton* bg9 = new QPushButton;
    QPushButton* bg10 = new QPushButton;
    QPushButton* bg11 = new QPushButton;
    QPushButton* bg12 = new QPushButton;
    QPushButton* bg13 = new QPushButton;
    QPushButton* bg14 = new QPushButton;
    QPushButton* bg15 = new QPushButton;
    QPushButton* bg16 = new QPushButton;

    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QHBoxLayout* layout3 = new QHBoxLayout;
    QHBoxLayout* layout4 = new QHBoxLayout;

    QLabel* changetip = new QLabel("请选择你的背景");
    QFont font;
    QVBoxLayout* ChangeLayout = new QVBoxLayout;
    QWidget *changebgw = new QWidget;

    my_tcpsocket* mtcp;
    int my_id;

    Ui::change_back *ui;
};

#endif // CHANGE_BACK_H
