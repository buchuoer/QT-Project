#include "my_tcpsocket.h"


my_tcpsocket::my_tcpsocket( QHostAddress hostAddress, int port, QObject *parent )
    :QTcpSocket(parent)
{
    connectToHost(hostAddress,port);
    connect(this, &QTcpSocket::readyRead, this, &my_tcpsocket::handleReadyRead);
}



void my_tcpsocket::handleReadyRead()
{
    QByteArray data = readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QString msgType=jsonObj.value("msgType").toString();
    qDebug()<<msgType;
    if(msgType=="LOGIN"||msgType=="REGISTER"){
        emit loginMessageReceived(jsonObj);
    }
    else if(msgType=="FRIEND_MESSAGE"){
        emit chatMessageReceived(jsonObj);
    }
    else if(msgType=="GROUP_MESSAGE"){
        emit chatMessageReceived(jsonObj);
    }
    else if(msgType=="ADD_FRIEND"){//消息提醒
        emit ListMessageReceived(jsonObj);
    }
    else if(msgType=="ACCEPT_FRIEND"){//不做回应

    }
    else if(msgType=="APPLY_PAL"){
        emit ListMessageReceived(jsonObj);
    }
    else if(msgType=="ACCEPT_PAL"){//不做回应

    }
    else if(msgType=="FRIEND_LIST"){
        emit ListMessageReceived(jsonObj);
    }
    else if(msgType=="GROUP_LIST"){
        emit ListMessageReceived(jsonObj);
    }
    else if(msgType=="TODO_LIST"){
        emit ListMessageReceived(jsonObj);
    }
    else if(msgType=="MYINFO"){//用户基本背景信息
        emit MyInfoReceived(jsonObj);
    }
    else if(msgType=="ONLINE_POSTS"){
        emit onlinepostMessageReceived(jsonObj);
    }
    else if(msgType=="USERPOSTS"){
        emit userpostMessageReceived(jsonObj);
    }
    else if(msgType=="USERINFO"){
        qDebug()<<"个人信息";
        emit userMessageReceived(jsonObj);
    }
}

my_tcpsocket::~my_tcpsocket() {}
