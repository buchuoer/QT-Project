#ifndef CHANGE_AVATAR_H
#define CHANGE_AVATAR_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "mainwindow.h"

namespace Ui {
class change_avatar;
}

class change_avatar : public QMainWindow
{
    Q_OBJECT

public:
    change_avatar(my_tcpsocket *tcp, int userId, QMainWindow *parent = nullptr);
    ~change_avatar();
    void Show(){
        changeavatarw->show();
    }
    void Hide(){
        changeavatarw->hide();
    }

private slots:
    void Avatar1Clicked();
    void Avatar2Clicked();
    void Avatar3Clicked();
    void Avatar4Clicked();
    void Avatar5Clicked();
    void Avatar6Clicked();
    void Avatar7Clicked();
    void Avatar8Clicked();
    void Avatar9Clicked();
    void Avatar10Clicked();
    void Avatar11Clicked();
    void Avatar12Clicked();
    void Avatar13Clicked();
    void Avatar14Clicked();
    void Avatar15Clicked();
    void Avatar16Clicked();

private:
    QPushButton* avatar1 = new QPushButton;
    QPushButton* avatar2 = new QPushButton;
    QPushButton* avatar3 = new QPushButton;
    QPushButton* avatar4 = new QPushButton;
    QPushButton* avatar5 = new QPushButton;
    QPushButton* avatar6 = new QPushButton;
    QPushButton* avatar7 = new QPushButton;
    QPushButton* avatar8 = new QPushButton;
    QPushButton* avatar9 = new QPushButton;
    QPushButton* avatar10 = new QPushButton;
    QPushButton* avatar11 = new QPushButton;
    QPushButton* avatar12 = new QPushButton;
    QPushButton* avatar13 = new QPushButton;
    QPushButton* avatar14 = new QPushButton;
    QPushButton* avatar15 = new QPushButton;
    QPushButton* avatar16 = new QPushButton;

    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QHBoxLayout* layout3 = new QHBoxLayout;
    QHBoxLayout* layout4 = new QHBoxLayout;

    QLabel* changetip = new QLabel("请选择你的头像");
    QFont font;
    QVBoxLayout* ChangeLayout = new QVBoxLayout;
    QWidget *changeavatarw = new QWidget;

    my_tcpsocket* mtcp;
    int my_id;



    Ui::change_avatar *ui;
};

#endif // CHANGE_AVATAR_H
