#include "mainwindow.h"
#include "mainwindow.h"
#include "change_avatar.h"
#include "change_back.h"
#include "change_name.h"
#include "person_dynamic.h"
#include "dynamic.h"
#include"release_post.h"
#include "pendingmessage.h"
MainWindow::MainWindow(my_tcpsocket* tcp, int userId, QWidget *parent)
    : QMainWindow(parent),
    w(new QWidget(this)) {

    mtcp = tcp;
    my_id = userId;
    QJsonObject jsonObj;

    connect(mtcp, &my_tcpsocket::MyInfoReceived, this, &MainWindow::handleMessage);


    jsonObj["msgType"]="MYINFO";
    jsonObj["id"]=my_id;


    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();

    mtcp->write(data);

    gender->setText("性别：");
    age->setText("年龄：");

    Gender->addWidget(gender);
    Gender->addWidget(change_gender);
    Age->addWidget(age);
    Age->addWidget(change_age);
    nga->addWidget(Name);
    nga->addLayout(Gender);
    nga->addLayout(Age);
    font.setPointSize(14);
    changeavatar->setText("修改头像");
    changeback->setText("修改背景");
    changename->setText("修改昵称");
    release->setText("发布征求");
    published->setText("征求大厅");
    mine->setText("我的征求");
    my_friend->setText("朋友列表");
    my_group->setText("群聊列表");
    add_friend->setText("添加朋友");
    todoList->setText("待办消息");



    layout0->addWidget(avatar);
    layout0->addLayout(nga);

    layout->addLayout(layout0);
    layout->addWidget(background);
    layout->addWidget(changeavatar);
    layout->addWidget(changeback);
    //layout->addWidget(changename);
    layout->addWidget(release);
    layout->addWidget(published);
    layout->addWidget(mine);
    layout->addWidget(my_friend);
    layout->addWidget(my_group);
    layout->addWidget(add_friend);
    layout->addWidget(todoList);

    w->setLayout(layout);
    setCentralWidget(w);

    setWindowTitle("搭一搭");//修改窗口名
    setFixedSize(480, 640);

    connect(changeavatar, &QPushButton::clicked, this, &MainWindow::ChangeClicked);
    connect(changeback, &QPushButton::clicked, this, &MainWindow::ChangebgClicked);
    connect(changename, &QPushButton::clicked, this, &MainWindow::ChangenameClicked);
    connect(release, &QPushButton::clicked, this, &MainWindow::ReleaseClicked);
    connect(published, &QPushButton::clicked, this, &MainWindow::PublishedClicked);
    connect(mine, &QPushButton::clicked, this, &::MainWindow::MineClicked);
    connect(my_friend, &QPushButton::clicked, this, &MainWindow::My_FriendClicked);
    connect(my_group, &QPushButton::clicked, this, &MainWindow::My_GroupClicked);
    connect(add_friend, &QPushButton::clicked, this, &MainWindow::Add_FriendClicked);
    connect(change_gender, &DoubleClickLineEdit::returnPressed, this, &MainWindow::Change_GenderClicked);
    connect(change_age, &DoubleClickLineEdit::returnPressed, this, &MainWindow::Change_AgeClicked);
    connect(addcommit, &QPushButton::clicked, this, &MainWindow::AddCommitClicked);
    connect(todoList, &QPushButton::clicked, this, &MainWindow::Todo_Clicked);
    qDebug()<<"初始界面构建完成！";
}

MainWindow::~MainWindow() {
    // 清理资源，如果有需要的话
}


void MainWindow::ChangeClicked() {
    // 在这里添加逻辑
    change_avatar *m = new change_avatar(mtcp, my_id);
    m->Show();
    delete this;
}

void MainWindow::ChangebgClicked(){
    change_back *m = new change_back(mtcp, my_id);
    m->Show();
    delete this;
}

void MainWindow::ChangenameClicked(){
    change_name *m = new change_name(mtcp, my_id);
    m->Show();
    this->close();
}
void MainWindow::ReleaseClicked() {
    // 在这里添加逻辑
    release_post * w=new release_post(mtcp,my_id);
    w->show();

}

void MainWindow::PublishedClicked() {
    //QMessageBox::information(this, "提示", "征求大厅按钮被点击了!");
    // 在这里添加逻辑
    Dynamic * dyna=new Dynamic(mtcp,my_id);
    dyna->show();
}

void MainWindow::MineClicked() {
    //QMessageBox::information(this, "提示", "我的征求按钮被点击了!");
    // 在这里添加逻辑
    Person_dynamic * per=new Person_dynamic(my_id,my_id,mtcp);
    per->show();
}

void MainWindow::My_FriendClicked() {
    //QMessageBox::information(this, "提示", "朋友列表按钮被点击了!");
    // 在这里添加逻辑
    //friendw->show();
    pendingmessage* w = new pendingmessage(mtcp, myInfo, "friendList");
    w->show();
}

void MainWindow::My_GroupClicked() {
    qDebug()<<"查看群列表";
    pendingmessage * w=new pendingmessage(mtcp,myInfo,"groupList");
    w->show();
}

void MainWindow::Todo_Clicked(){
    pendingmessage * w=new pendingmessage(mtcp,myInfo,"todoList");
    w->show();
}

void MainWindow::Add_FriendClicked() {
    //QMessageBox::information(this, "提示", "添加朋友按钮被点击了!");
    // 在这里添加逻辑

    QHBoxLayout* addlayout = new QHBoxLayout;
    addfriend->setPlaceholderText("输入好友的用户名");
    addcommit->setText("发送申请");
    addcommit->setFixedSize(60, 30);
    addlayout->addWidget(addfriend);
    addlayout->addWidget(addcommit);
    addw->setLayout(addlayout);
    addw->setWindowTitle("搭一搭");
    addw->show();

}

void MainWindow::AddCommitClicked(){
    QString searchname = addfriend->text();
    QJsonObject jsonObj;

    jsonObj["msgType"]="ADD_FRIEND";
    jsonObj["userName"]=searchname;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("M/d/yy  hh:mm");
    jsonObj["timestamp"]=formattedDateTime ;
    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();

    mtcp->write(data);
    addw->close();
    QMessageBox::information(this, "提示", "发送成功！");


}
void MainWindow::Change_GenderClicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_SEX";
    jsonObj["id"]=my_id;

    QString newgender = change_gender->text();
    if(newgender == "男"){
        change_gender->setPlaceholderText("男");
        jsonObj["serial"]=1;
        QMessageBox::information(this, "提示", "修改成功！");
        change_gender->clear();
    }
    else if(newgender == "女"){
        change_gender->setPlaceholderText("女");
        jsonObj["serial"]=0;
        QMessageBox::information(this, "提示", "修改成功！");
        change_gender->clear();
    }
    else QMessageBox::information(this, "提示", "输入不合法！");change_gender->clear();

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
}
void MainWindow::Change_AgeClicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_AGE";
    jsonObj["id"]=my_id;
    bool ok;
    int newage = change_age->text().toInt(&ok);
    if(ok == 0){
        QMessageBox::information(this, "提示", "输入不合法！");
        change_age->clear();
    }
    else{
        if(newage<=0){
            QMessageBox::information(this, "提示", "输入不合法！");
            change_age->clear();
        }
        else{
            jsonObj["serial"]=newage;
            QString late = QString::number(newage);
            change_age->setPlaceholderText(late);
            QMessageBox::information(this, "提示", "修改成功！");
            change_age->clear();
        }
    }
    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);

}
void MainWindow::handleMessage(const QJsonObject& jsonObj){
    myInfo = jsonObj;
    name = jsonObj.value("username").toString();
    avatar_id = jsonObj.value("profile").toInt();
    bg_id = jsonObj.value("bgPhoto").toInt();
    if(jsonObj.value("sex").toInt() == 1){
        gender_id = "男";
    }
    else gender_id = "女";
    age_id = QString::number(jsonObj.value("age").toInt());
    Name->setText(name);
    Name->setFont(font);
    change_gender->setPlaceholderText(gender_id);
    change_age->setPlaceholderText(age_id);
    qDebug()<<name<<avatar_id<<bg_id;
//    QString imagepath=:/new/prefix1/E:/dynamic/image/3.jpg;
//  QString imagepath="E:\\dynamic\\image\\";
//    QPixmap pro(imagepath+QString::number(profile)+".jpg");
//
    QPixmap Picture1("://picture/avatar/1.jpg");
    QPixmap Picture2("://picture/avatar/2.jpg");
    QPixmap Picture3("://picture/avatar/3.jpg");
    QPixmap Picture4("://picture/avatar/4.jpg");
    QPixmap Picture5("://picture/avatar/5.jpg");
    QPixmap Picture6("://picture/avatar/6.jpg");
    QPixmap Picture7("://picture/avatar/7.jpg");
    QPixmap Picture8("://picture/avatar/8.jpg");
    QPixmap Picture9("://picture/avatar/9.jpg");
    QPixmap Picture10("://picture/avatar/10.jpg");
    QPixmap Picture11("://picture/avatar/11.jpg");
    QPixmap Picture12("://picture/avatar/12.jpg");
    QPixmap Picture13("://picture/avatar/13.jpg");
    QPixmap Picture14("://picture/avatar/14.jpg");
    QPixmap Picture15("://picture/avatar/15.jpg");
    QPixmap Picture16("://picture/avatar/16.jpg");

    Picture1 = Picture1.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture2 = Picture2.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture3 = Picture3.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture4 = Picture4.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture5 = Picture5.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture6 = Picture6.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture7 = Picture7.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture8 = Picture8.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture9 = Picture9.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture10 = Picture10.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture11 = Picture11.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture12 = Picture12.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture13 = Picture13.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture14 = Picture14.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture15 = Picture15.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture16 = Picture16.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    switch (MainWindow::avatar_id){
    case 1: avatar->setPixmap(Picture1);break;
    case 2: avatar->setPixmap(Picture2);break;
    case 3: avatar->setPixmap(Picture3);break;
    case 4: avatar->setPixmap(Picture4);break;
    case 5: avatar->setPixmap(Picture5);break;
    case 6: avatar->setPixmap(Picture6);break;
    case 7: avatar->setPixmap(Picture7);break;
    case 8: avatar->setPixmap(Picture8);break;
    case 9: avatar->setPixmap(Picture9);break;
    case 10: avatar->setPixmap(Picture10);break;
    case 11: avatar->setPixmap(Picture11);break;
    case 12: avatar->setPixmap(Picture12);break;
    case 13: avatar->setPixmap(Picture13);break;
    case 14: avatar->setPixmap(Picture14);break;
    case 15: avatar->setPixmap(Picture15);break;
    case 16: avatar->setPixmap(Picture16);break;
    }


    QPixmap picture1("://picture/background/1.jpg");
    QPixmap picture2("://picture/background/2.jpg");
    QPixmap picture3("://picture/background/3.jpg");
    QPixmap picture4("://picture/background/4.jpg");
    QPixmap picture5("://picture/background/5.jpg");
    QPixmap picture6("://picture/background/6.jpg");
    QPixmap picture7("://picture/background/7.jpg");
    QPixmap picture8("://picture/background/8.jpg");
    QPixmap picture9("://picture/background/9.jpg");
    QPixmap picture10("://picture/background/10.jpg");
    QPixmap picture11("://picture/background/11.jpg");
    QPixmap picture12("://picture/background/12.jpg");
    QPixmap picture13("://picture/background/13.jpg");
    QPixmap picture14("://picture/background/14.jpg");
    QPixmap picture15("://picture/background/15.jpg");
    QPixmap picture16("://picture/background/16.jpg");

    picture1 = picture1.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture2 = picture2.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture3 = picture3.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture4 = picture4.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture5 = picture5.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture6 = picture6.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture7 = picture7.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture8 = picture8.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture9 = picture9.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture10 = picture10.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture11 = picture11.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture12 = picture12.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture13 = picture13.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture14 = picture14.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture15 = picture15.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picture16 = picture16.scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    switch (MainWindow::bg_id){
    case 1: background->setPixmap(picture1);break;
    case 2: background->setPixmap(picture2);break;
    case 3: background->setPixmap(picture3);break;
    case 4: background->setPixmap(picture4);break;
    case 5: background->setPixmap(picture5);break;
    case 6: background->setPixmap(picture6);break;
    case 7: background->setPixmap(picture7);break;
    case 8: background->setPixmap(picture8);break;
    case 9: background->setPixmap(picture9);break;
    case 10: background->setPixmap(picture10);break;
    case 11: background->setPixmap(picture11);break;
    case 12: background->setPixmap(picture12);break;
    case 13: background->setPixmap(picture13);break;
    case 14: background->setPixmap(picture14);break;
    case 15: background->setPixmap(picture15);break;
    case 16: background->setPixmap(picture16);break;
    }


}
