#include "change_back.h"
#include "mainwindow.h"


change_back::change_back(my_tcpsocket *tcp, int userId, QWidget *parent)
    : QWidget(parent)
{
    mtcp = tcp;
    my_id = userId;

    connect(bg1, &QPushButton::clicked, this, &change_back::Background1Clicked);
    connect(bg2, &QPushButton::clicked, this, &change_back::Background2Clicked);
    connect(bg3, &QPushButton::clicked, this, &change_back::Background3Clicked);
    connect(bg4, &QPushButton::clicked, this, &change_back::Background4Clicked);
    connect(bg5, &QPushButton::clicked, this, &change_back::Background5Clicked);
    connect(bg6, &QPushButton::clicked, this, &change_back::Background6Clicked);
    connect(bg7, &QPushButton::clicked, this, &change_back::Background7Clicked);
    connect(bg8, &QPushButton::clicked, this, &change_back::Background8Clicked);
    connect(bg9, &QPushButton::clicked, this, &change_back::Background9Clicked);
    connect(bg10, &QPushButton::clicked, this, &change_back::Background10Clicked);
    connect(bg11, &QPushButton::clicked, this, &change_back::Background11Clicked);
    connect(bg12, &QPushButton::clicked, this, &change_back::Background12Clicked);
    connect(bg13, &QPushButton::clicked, this, &change_back::Background13Clicked);
    connect(bg14, &QPushButton::clicked, this, &change_back::Background14Clicked);
    connect(bg15, &QPushButton::clicked, this, &change_back::Background15Clicked);
    connect(bg16, &QPushButton::clicked, this, &change_back::Background16Clicked);

    QIcon picture1("://picture/background/1.jpg");
    QIcon picture2("://picture/background/2.jpg");
    QIcon picture3("://picture/background/3.jpg");
    QIcon picture4("://picture/background/4.jpg");
    QIcon picture5("://picture/background/5.jpg");
    QIcon picture6("://picture/background/6.jpg");
    QIcon picture7("://picture/background/7.jpg");
    QIcon picture8("://picture/background/8.jpg");
    QIcon picture9("://picture/background/9.jpg");
    QIcon picture10("://picture/background/10.jpg");
    QIcon picture11("://picture/background/11.jpg");
    QIcon picture12("://picture/background/12.jpg");
    QIcon picture13("://picture/background/13.jpg");
    QIcon picture14("://picture/background/14.jpg");
    QIcon picture15("://picture/background/15.jpg");
    QIcon picture16("://picture/background/16.jpg");

    bg1 ->setIcon(picture1);
    bg2 ->setIcon(picture2);
    bg3 ->setIcon(picture3);
    bg4 ->setIcon(picture4);
    bg5 ->setIcon(picture5);
    bg6 ->setIcon(picture6);
    bg7 ->setIcon(picture7);
    bg8 ->setIcon(picture8);
    bg9 ->setIcon(picture9);
    bg10->setIcon(picture10);
    bg11->setIcon(picture11);
    bg12->setIcon(picture12);
    bg13->setIcon(picture13);
    bg14->setIcon(picture14);
    bg15->setIcon(picture15);
    bg16->setIcon(picture16);

    bg1 ->setIconSize(QSize(256, 144));
    bg2 ->setIconSize(QSize(256, 144));
    bg3 ->setIconSize(QSize(256, 144));
    bg4 ->setIconSize(QSize(256, 144));
    bg5 ->setIconSize(QSize(256, 144));
    bg6 ->setIconSize(QSize(256, 144));
    bg7 ->setIconSize(QSize(256, 144));
    bg8 ->setIconSize(QSize(256, 144));
    bg9 ->setIconSize(QSize(256, 144));
    bg10 ->setIconSize(QSize(256, 144));
    bg11 ->setIconSize(QSize(256, 144));
    bg12 ->setIconSize(QSize(256, 144));
    bg13 ->setIconSize(QSize(256, 144));
    bg14 ->setIconSize(QSize(256, 144));
    bg15 ->setIconSize(QSize(256, 144));
    bg16 ->setIconSize(QSize(256, 144));

    layout1->addWidget(bg1);
    layout1->addWidget(bg2);
    layout1->addWidget(bg3);
    layout1->addWidget(bg4);
    layout2->addWidget(bg5);
    layout2->addWidget(bg6);
    layout2->addWidget(bg7);
    layout2->addWidget(bg8);
    layout3->addWidget(bg9);
    layout3->addWidget(bg10);
    layout3->addWidget(bg11);
    layout3->addWidget(bg12);
    layout4->addWidget(bg13);
    layout4->addWidget(bg14);
    layout4->addWidget(bg15);
    layout4->addWidget(bg16);

    font.setPointSize(14);
    changetip->setFont(font);

    ChangeLayout->addWidget(changetip);
    ChangeLayout->addLayout(layout1);
    ChangeLayout->addLayout(layout2);
    ChangeLayout->addLayout(layout3);
    ChangeLayout->addLayout(layout4);

    changebgw->setLayout(ChangeLayout);

    changebgw->setWindowTitle("搭一搭");

}
void change_back::Background1Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=1;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background2Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=2;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background3Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=3;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background4Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=4;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background5Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=5;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background6Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=6;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background7Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=7;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background8Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=8;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background9Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=9;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background10Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=10;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background11Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=11;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background12Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=12;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background13Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=13;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background14Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=14;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background15Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=15;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
void change_back::Background16Clicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=16;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

    QMessageBox::information(this, "提示", "设置成功!");

    MainWindow *w = new MainWindow(this->mtcp, this->my_id);
    changebgw->close();
    w->show();
}
change_back::~change_back()
{

}
