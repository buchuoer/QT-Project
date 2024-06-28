#include "todoitem.h"
#include "ui_todoitem.h"

todoItem::todoItem(my_tcpsocket * socket,const QJsonObject & msgObj_ , QWidget *parent )
    : QWidget(parent),mtcp(socket),msgObj(msgObj_)
    , ui(new Ui::todoItem)
{
    ui->setupUi(this);
    int profile=msgObj.value("profile").toInt();
    QString senderName=msgObj.value("senderName").toString();
    QString timestamp=msgObj.value("timestamp").toString();
    //ui->profileButton 头像设置
    QString imagepath="://picture/avatar/";
    QIcon buttonIcon(imagepath+QString::number(profile)+".jpg");
    ui->profileButton->setIcon(buttonIcon);//头像设置
    ui->profileButton->setIconSize({31,31});


    ui->usernameText->setText(senderName);
    qDebug()<<"列表成员"<<senderName;
    ui->timeText->setText(timestamp);
    qDebug()<<"代办时间"<<timestamp;
    if(msgObj.contains("postId")){
        QString postName=msgObj.value("postName").toString();
        QString msgtext=QString("申请成为你的 【 %1 】 搭子").arg(postName);
        ui->msgText->setText(msgtext);
    }
    else{
        ui->msgText->setText("申请添加您为好友");
    }
}

todoItem::~todoItem()
{
    delete ui;
}

void todoItem::on_agreeButton_clicked()
{
    QString msgType=msgObj.value("msgType").toString();
    QString msgtype;
    if(msgType=="ADD_FRIEND"){
        msgtype="ACCEPT_FRIEND";
    }
    else if(msgType=="APPLY_PAL"){
        msgtype="ACCEPT_PAL";
    }
    int receiverId=msgObj.value("senderId").toInt();

    QJsonObject jsonObj2;
    jsonObj2["msgType"]=msgtype;
    jsonObj2["receiverId"]=receiverId;
    if(msgtype=="ACCEPT_PAL"){
        jsonObj2["postId"]=msgObj.value("postId").toInt();
    }
    jsonObj2["msgId"]=msgObj.value("msgId").toInt();
    qDebug()<<"同意"<<receiverId<<"的申请";
    QJsonDocument jsonDoc2(jsonObj2);
    QByteArray data_ = jsonDoc2.toJson();
    mtcp->write(data_);
    delete this;
}


void todoItem::on_disagreeButton_clicked()
{
    QJsonObject jsonObj2;
    jsonObj2["msgId"]=msgObj.value("msgId").toInt();
    jsonObj2["msgType"]="DISAGREE";
    QJsonDocument jsonDoc2(jsonObj2);
    QByteArray data_ = jsonDoc2.toJson();
    mtcp->write(data_);
    delete this;
}

