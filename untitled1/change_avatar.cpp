#include "change_avatar.h"
#include "mainwindow.h"


change_avatar::change_avatar(my_tcpsocket *tcp, int userId, QMainWindow *parent)
    : QMainWindow(parent)
{
    mtcp = tcp;
    my_id = userId;


    connect(avatar1, &QPushButton::clicked, this, &change_avatar::Avatar1Clicked);
    connect(avatar2, &QPushButton::clicked, this, &change_avatar::Avatar2Clicked);
    connect(avatar3, &QPushButton::clicked, this, &change_avatar::Avatar3Clicked);
    connect(avatar4, &QPushButton::clicked, this, &change_avatar::Avatar4Clicked);
    connect(avatar5, &QPushButton::clicked, this, &change_avatar::Avatar5Clicked);
    connect(avatar6, &QPushButton::clicked, this, &change_avatar::Avatar6Clicked);
    connect(avatar7, &QPushButton::clicked, this, &change_avatar::Avatar7Clicked);
    connect(avatar8, &QPushButton::clicked, this, &change_avatar::Avatar8Clicked);
    connect(avatar9, &QPushButton::clicked, this, &change_avatar::Avatar9Clicked);
    connect(avatar10, &QPushButton::clicked, this, &change_avatar::Avatar10Clicked);
    connect(avatar11, &QPushButton::clicked, this, &change_avatar::Avatar11Clicked);
    connect(avatar12, &QPushButton::clicked, this, &change_avatar::Avatar12Clicked);
    connect(avatar13, &QPushButton::clicked, this, &change_avatar::Avatar13Clicked);
    connect(avatar14, &QPushButton::clicked, this, &change_avatar::Avatar14Clicked);
    connect(avatar15, &QPushButton::clicked, this, &change_avatar::Avatar15Clicked);
    connect(avatar16, &QPushButton::clicked, this, &change_avatar::Avatar16Clicked);

    QIcon picture1("://picture/avatar/1.jpg");
    QIcon picture2("://picture/avatar/2.jpg");
    QIcon picture3("://picture/avatar/3.jpg");
    QIcon picture4("://picture/avatar/4.jpg");
    QIcon picture5("://picture/avatar/5.jpg");
    QIcon picture6("://picture/avatar/6.jpg");
    QIcon picture7("://picture/avatar/7.jpg");
    QIcon picture8("://picture/avatar/8.jpg");
    QIcon picture9("://picture/avatar/9.jpg");
    QIcon picture10("://picture/avatar/10.jpg");
    QIcon picture11("://picture/avatar/11.jpg");
    QIcon picture12("://picture/avatar/12.jpg");
    QIcon picture13("://picture/avatar/13.jpg");
    QIcon picture14("://picture/avatar/14.jpg");
    QIcon picture15("://picture/avatar/15.jpg");
    QIcon picture16("://picture/avatar/16.jpg");

    avatar1 ->setIcon(picture1);
    avatar2 ->setIcon(picture2);
    avatar3 ->setIcon(picture3);
    avatar4 ->setIcon(picture4);
    avatar5 ->setIcon(picture5);
    avatar6 ->setIcon(picture6);
    avatar7 ->setIcon(picture7);
    avatar8 ->setIcon(picture8);
    avatar9 ->setIcon(picture9);
    avatar10->setIcon(picture10);
    avatar11->setIcon(picture11);
    avatar12->setIcon(picture12);
    avatar13->setIcon(picture13);
    avatar14->setIcon(picture14);
    avatar15->setIcon(picture15);
    avatar16->setIcon(picture16);

    avatar1 ->setIconSize(QSize(80, 80));
    avatar2 ->setIconSize(QSize(80, 80));
    avatar3 ->setIconSize(QSize(80, 80));
    avatar4 ->setIconSize(QSize(80, 80));
    avatar5 ->setIconSize(QSize(80, 80));
    avatar6 ->setIconSize(QSize(80, 80));
    avatar7 ->setIconSize(QSize(80, 80));
    avatar8 ->setIconSize(QSize(80, 80));
    avatar9 ->setIconSize(QSize(80, 80));
    avatar10->setIconSize(QSize(80, 80));
    avatar11->setIconSize(QSize(80, 80));
    avatar12->setIconSize(QSize(80, 80));
    avatar13->setIconSize(QSize(80, 80));
    avatar14->setIconSize(QSize(80, 80));
    avatar15->setIconSize(QSize(80, 80));
    avatar16->setIconSize(QSize(80, 80));

    layout1->addWidget(avatar1);
    layout1->addWidget(avatar2);
    layout1->addWidget(avatar3);
    layout1->addWidget(avatar4);
    layout2->addWidget(avatar5);
    layout2->addWidget(avatar6);
    layout2->addWidget(avatar7);
    layout2->addWidget(avatar8);
    layout3->addWidget(avatar9);
    layout3->addWidget(avatar10);
    layout3->addWidget(avatar11);
    layout3->addWidget(avatar12);
    layout4->addWidget(avatar13);
    layout4->addWidget(avatar14);
    layout4->addWidget(avatar15);
    layout4->addWidget(avatar16);

    font.setPointSize(14);
    changetip->setFont(font);

    ChangeLayout->addWidget(changetip);
    ChangeLayout->addLayout(layout1);
    ChangeLayout->addLayout(layout2);
    ChangeLayout->addLayout(layout3);
    ChangeLayout->addLayout(layout4);

    changeavatarw->setLayout(ChangeLayout);

    changeavatarw->setWindowTitle("搭一搭");

}
void change_avatar::Avatar1Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=1;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar2Clicked(){

    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=2;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar3Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=3;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar4Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=4;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar5Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=5;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar6Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=6;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}

void change_avatar::Avatar7Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=7;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar8Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=8;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar9Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=9;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar10Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=10;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar11Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=11;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar12Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=12;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar13Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=13;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar14Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=14;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar15Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=15;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
void change_avatar::Avatar16Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_PROFILE";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=16;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    qDebug()<<"update profile";
    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changeavatarw->close();
    w->show();
}
change_avatar::~change_avatar()
{

}
