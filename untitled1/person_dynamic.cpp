#include "person_dynamic.h"
#include "ui_person_dynamic.h"
#include"post_item.h"
#include<QJsonArray>
Person_dynamic::Person_dynamic(int myid_,int hostid_,my_tcpsocket * socket,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Person_dynamic),mtcp(socket),myid(myid_),hostid(hostid_)
{
    ui->setupUi(this);
    this->setWindowTitle("搭一搭");
    QJsonObject jsonobj;
    jsonobj["msgType"]="USERPOSTS";
    jsonobj["userId"]=hostid;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    connect(mtcp, &my_tcpsocket::userpostMessageReceived, this, &Person_dynamic::handleMessage);
}
void Person_dynamic::addMessage(const QJsonObject& jsonObj){//const QJsonObject& jsonObj,QString name
    int publishStatus=jsonObj.value("publishStatus").toInt();
    qDebug()<<"Person_dynamic::addMessage"<<publishStatus;
    if((myid!=hostid&&publishStatus==1)||myid==hostid){
        post_item* add=new post_item(myid,hostid,mtcp);
        add->setDate(jsonObj);//,name

        QListWidgetItem *m_item=new QListWidgetItem(ui->listWidget);

        m_item->setSizeHint(QSize(470,275));
        ui->listWidget->setItemWidget(m_item,add);
    }

}
void Person_dynamic::handleMessage(const QJsonObject& jsonObj){//相当于更新数据
    qDebug()<<"Person_dynamic::handleMessage";

    QJsonArray onlinePosts=jsonObj.value("jsonArray").toArray();
    qDebug()<<"onlinePosts.size()"<<onlinePosts.size();
    for (QJsonArray::iterator it = onlinePosts.begin(); it != onlinePosts.end(); ++it) {
        if (it->isObject()) {
            QJsonObject postmessage =  (*it).toObject();
            addMessage(postmessage);//,name
        }
    }
}
//删除功能

//完成功能
Person_dynamic::~Person_dynamic()
{
    delete ui;
}
