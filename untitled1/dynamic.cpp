#include "dynamic.h"
#include "ui_dynamic.h"
#include"post_item.h"

#include"release_post.h"
#include <QJsonArray>
#include<QDebug>
Dynamic::Dynamic(my_tcpsocket * socket,int myid_,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dynamic),mtcp(socket),myid(myid_)
{

    ui->setupUi(this);
    this->setWindowTitle("社交大厅");
    QJsonObject jsonobj;
    jsonobj["msgType"]="ONLINE_POSTS";
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    connect(mtcp, &my_tcpsocket::onlinepostMessageReceived, this, &Dynamic::handleMessage);
}

Dynamic::~Dynamic()
{
    delete ui;
}
void Dynamic::addMessage(const QJsonObject& jsonObj){//,QString name
    qDebug()<<"开始添加";
    int userid=jsonObj.value("userId").toInt();
    qDebug()<<"userid"<<userid;
    post_item* add=new post_item(myid,userid,mtcp);
    add->setDate(jsonObj);//,name
    QListWidgetItem *m_item=new QListWidgetItem(ui->listWidget);
    m_item->setSizeHint(QSize(470,275));
    ui->listWidget->setItemWidget(m_item,add);
}
void Dynamic::handleMessage(const QJsonObject& jsonObj)//从数据库里面连续读入数据
{
//    timestamp=jsonObj.value("timestamp").toString();
    qDebug()<<"Dynamic::handleMessage";
    QJsonArray onlinePosts=jsonObj.value("jsonArray").toArray();
    qDebug()<<"onlinePosts.size()"<<onlinePosts.size();
    for (QJsonArray::iterator it = onlinePosts.begin(); it != onlinePosts.end(); ++it) {
        if (it->isObject()) {
            QJsonObject postmessage =  (*it).toObject();
/*            int senderid=postmessage.value("userId").toInt();
          QString name=postmessage.value("username").toString();
            QString state=postmessage.value("status").toString();
            QString content=postmessage.value("content").toString();
            QString timestamp=postmessage.value("timestamp").toString();
            QString type=postmessage.value("kind").toString();
            int postId_=postmessage.value("postId").toInt();
            qDebug()<<senderid;
*/          postmessage["publishStatus"]=1;
            addMessage(postmessage);//,name
        }
    }
}

void Dynamic::on_pushButton_release_clicked()//点击后弹出发布窗口
{
    this->hide();
    release_post * w=new release_post(mtcp,myid);
    w->show();
//    connect(w,&release_post::back,this,&Dynamic::backupDate);
}


void Dynamic::on_pushButton_return_clicked()
{
    this->close();
}
void Dynamic::upDate(){
    qDebug()<<"发布成功后，重新连接数据库";
    Dynamic * w=new Dynamic(mtcp,myid);
    delete this;
    w->show();
}
