#include "chat_window.h"
#include "ui_chat_window.h"

chat_window::chat_window(my_tcpsocket * socket, int firendId_,QString friendName_, int fdProfile_,
                         int myId_, QString myName_, int myProfile_, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chat_window),friendId(firendId_), friendName(friendName_),fdProfile(fdProfile_),
    myId(myId_),myName(myName_), myProfile(myProfile_),mtcp (socket)
{
    ui->setupUi(this);
    connect(mtcp, &my_tcpsocket::chatMessageReceived, this, &chat_window::handleMessage);
    ui->friendNameText->setHtml("<center>"+friendName+"</center>");//居中好友名字
    //ui->friendNameText->setPlainText(friendName);
    setWindowTitle("搭一搭");
}

chat_window::chat_window(my_tcpsocket * socket,int groupId_,
                         QString groupName_,int myId_, QString myName_, int myProfile_,QWidget *parent )

    : QWidget(parent)
    , ui(new Ui::chat_window),
    myId(myId_),myName(myName_), myProfile(myProfile_),mtcp (socket),groupId(groupId_),groupName(groupName_)
{
    ui->setupUi(this);
    connect(mtcp, &my_tcpsocket::chatMessageReceived, this, &chat_window::handleMessage);
    ui->friendNameText->setHtml("<center>"+groupName+"</center>");//居中好友名字
}

chat_window::~chat_window()
{
    delete ui;
}

void chat_window::on_msgSendButton_released()
{
    QString message = ui->lineEdit->text();
    ui->lineEdit->clear();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("M/d/yy  hh:mm");
    addMessage(myName,myProfile,message,formattedDateTime);
    QJsonObject jsonObj;
    if(friendId){
        jsonObj["msgType"]="FRIEND_MESSAGE";
        jsonObj["receiverId"]=friendId;
        qDebug()<<"向他发送消息"<<friendId;
        jsonObj["msg"]=message;
        qDebug()<<message;
    }
    else if(groupId){
        jsonObj["msgType"]="GROUP_MESSAGE";
        jsonObj["groupId"]=groupId;
        qDebug()<<"向群发送消息"<<groupName;
        jsonObj["msg"]=message;
    }

    jsonObj["timestamp"]=formattedDateTime;
    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
}

void chat_window::handleMessage(const QJsonObject& jsonObj)
{
    int GroupId=jsonObj.value("groupId").toInt();
    int senderId=jsonObj.value("senderId").toInt();
    if(senderId==friendId){
        QString msg=jsonObj.value("msg").toString(),timestamp=jsonObj.value("timestamp").toString();
        //int id=jsonObj.value("senderId").toInt();
        qDebug()<<msg;
        addMessage(friendName,fdProfile,msg,timestamp);
    }
    else if(groupId==GroupId){
        QString name=jsonObj.value("username").toString(),msg=jsonObj.value("msg").toString()
            ,timestamp=jsonObj.value("timestamp").toString();
        int profile=jsonObj.value("profile").toInt();
        addMessage(name,profile,msg,timestamp);

    }

}
void chat_window::addMessage(const QString &senderName,int profile, const QString &message,const QString &timestamp) {
    MessageItem *itemWidget = new MessageItem(profile,senderName, message,timestamp);
    QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
    listWidgetItem->setSizeHint(QSize(387,58));//itemWidget->sizeHint()
    ui->listWidget->setItemWidget(listWidgetItem, itemWidget);
}
void chat_window::on_msgEdit_returnPressed()
{

}
