#include "pendingmessage.h"
#include "ui_pendingmessage.h"
#include "frienditem.h"
#include "groupitem.h"
#include "todoitem.h"
pendingmessage:: pendingmessage(my_tcpsocket * socket, QJsonObject myInfo_,QString type_, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pendingmessage),mtcp(socket),type(type_)
{
    QJsonObject jsonObj;
    ui->setupUi(this);
    if(type=="friendList"){
        ui->titleName->setText("好友列表");
        jsonObj["msgType"]="FRIEND_LIST";
    }
    else if(type=="groupList"){
        ui->titleName->setText("群聊列表");
        jsonObj["msgType"]="GROUP_LIST";
    }
    else if(type=="todoList"){
        ui->titleName->setText("待办消息");
        jsonObj["msgType"]="TODO_LIST";
    }
    //jsonObj["userId"]=myId;
    QJsonDocument jsonDoc(jsonObj);
    QByteArray data=jsonDoc.toJson();


    mtcp->write(data);
    qDebug()<<type<<"创建";
    connect(mtcp ,&my_tcpsocket::ListMessageReceived, this, &pendingmessage::handleMessage);
    myInfo = myInfo_;
    setWindowTitle("搭一搭");

}
void pendingmessage::handleMessage(const QJsonObject & jsonObj)
{
    QString msgType=jsonObj.value("msgType").toString();
    QJsonArray jsonArray=jsonObj.value("jsonArray").toArray();
    qDebug()<<jsonArray.size();
    if(jsonArray.size()){
        qDebug()<<"待办非空";
    }
    if(msgType=="FRIEND_LIST"&&type=="friendList"){
        qDebug()<<"recieve FRIEND_LIST";
        for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it) {
            if (it->isObject()) {
                QJsonObject friendObj =  (*it).toObject();
                int friendId=friendObj.value("userId").toInt(),profile=friendObj.value("profile").toInt();
                QString friendName=friendObj.value("username").toString();
                qDebug()<<"好友列表"<<friendId;
                addMessage(myInfo,friendId,friendName,profile);
            }
        }
    }
    else if(msgType=="GROUP_LIST"&&type=="groupList"){
        for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it) {
            if (it->isObject()) {
                QJsonObject groupObj =  (*it).toObject();
                int groupId=groupObj.value("groupId").toInt();
                QString groupName=groupObj.value("groupName").toString();
                addMessage(myInfo,groupId,groupName);
            }
        }
    }
    else if(msgType=="TODO_LIST"&&type=="todoList"){
        for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it) {
            if (it->isObject()) {
                QJsonObject todoObj =  (*it).toObject();
                qDebug()<<"待办预添加"<<todoObj.value("senderName").toString();
                addMessage(todoObj);
                // QJsonObject todoObj =  (*it).toObject();
                // int msgId=todoObj.value("msgId").toInt();
                // QString todoType=todoObj.value("msgType").toString();
                // int senderId=todoObj.value("senderId").toInt();
                // QString timestamp=todoObj.value("timestamp").toString();

                // if(todoType=="APPLY_FRIEND"){
                // }
                // else if(todoType=="APPLY_PAL"){
                //     int postId=todoObj.value("postId").toInt();
                // }
            }
        }




    }
}
void pendingmessage::addMessage(QJsonObject myInfo,int Id,QString Name,int profile)
{
    qDebug()<<"好友成员"<<Name<<"头像"<<profile;
    friendItem * add=new friendItem(mtcp,myInfo,Id,Name,profile);
    QListWidgetItem *m_item=new QListWidgetItem(ui->listWidget);
    m_item->setSizeHint(QSize(413,42));
    ui->listWidget->setItemWidget(m_item,add);
}

void pendingmessage::addMessage(QJsonObject myInfo,int Id,QString Name)
{
    groupItem * add=new groupItem(mtcp,myInfo,Id,Name);
    QListWidgetItem *m_item=new QListWidgetItem(ui->listWidget);
    m_item->setSizeHint(QSize(413,42));
    ui->listWidget->setItemWidget(m_item,add);
}
void pendingmessage::addMessage(const QJsonObject & msgObj){
    todoItem * add=new todoItem(mtcp,msgObj);
    QListWidgetItem *m_item=new QListWidgetItem(ui->listWidget);
    m_item->setSizeHint(QSize(413,42));
    ui->listWidget->setItemWidget(m_item,add);
}


pendingmessage::~pendingmessage()
{
    delete ui;
}
