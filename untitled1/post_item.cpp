#include "post_item.h"
#include "ui_post_item.h"
//#include "person_dynamic.h"
#include "person_message.h"
#include "my_tcpsocket.h"
#include<QPixmap>
post_item::post_item(int myid_,int senderid_,my_tcpsocket * socket,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::post_item),mtcp(socket),myid(myid_),senderid(senderid_)//按钮是私有的设置按钮状态
{
    ui->setupUi(this);
    ui->pushButton_delete->hide();
    ui->pushButton_end->hide();
    ui->pushButton_over->hide();
}

post_item::~post_item()
{
    delete ui;
}
void post_item::setDate(const QJsonObject& jsonObj){//,QString name，int profile
    //senderid=jsonObj.value("userId").toInt();
    //QString name=postmessage.value("username").toString();
    int publishStatus=jsonObj.value("publishStatus").toInt();
    QString content=jsonObj.value("content").toString();//直接打包传输的话
    QString timestamp=jsonObj.value("timestamp").toString();
    QString username=jsonObj.value("username").toString();
    QString type=jsonObj.value("kind").toString();
    postId=jsonObj.value("postId").toInt();
//    int profile=jsonObj.value("profile").toInt();
    qDebug()<<"publishStatus"<<publishStatus;
    qDebug()<<myid<<" "<<senderid;

    if(myid==senderid&&publishStatus==1){
        ui->pushButton_join->hide();
        ui->pushButton_delete->show();
        ui->pushButton_end->show();
        ui->pushButton_over->show();
    }else if(myid!=senderid&&publishStatus==1){
        int joined=jsonObj.value("joined").toInt();
        if(joined==1) ui->pushButton_join->hide();
        qDebug()<<"joined"<<joined;
    }else if(myid==senderid&&publishStatus==0){
        ui->pushButton_join->hide();
        ui->pushButton_delete->show();
        ui->pushButton_over->show();
    }else if(myid==senderid&&publishStatus==-1){
        ui->pushButton_join->hide();
        ui->pushButton_delete->show();
    }
    ui->label_time->setText(timestamp);
    ui->textBrowser->setText(content);
    ui->label_type->setText(type);
    ui->label_name->setText(username);
    int profile=jsonObj["profile"].toInt();
    QString imagepath="://picture/avatar/";
    QPixmap pro(imagepath+QString::number(profile)+".jpg");
    QPixmap pro2=pro.scaled(ui->pushButton_user->size(),Qt::KeepAspectRatio);
    QIcon buttonIcon(pro2);
    ui->pushButton_user->setIcon(buttonIcon);
    ui->pushButton_user->setIconSize(ui->pushButton_user->size());
    qDebug()<<"设置图片";
}
void post_item::on_pushButton_user_clicked()
{
    //个人信息页面
    //id
    person_message * otheruser=new person_message(mtcp,senderid,myid);
    otheruser->show();
}


void post_item::on_pushButton_join_clicked()//发送消息给发布者，征求发布者同意，加入群聊
{
    //向发布者发送链接
    //if(){//已参加已参加设置在setDate就已经完成了
    //}
    //else{
        QJsonObject jsonobj;
        jsonobj["msgType"]="APPLY_PAL";
        jsonobj["receiverId"]=senderid;
        jsonobj["postId"]=postId;
        QJsonDocument jsonDoc(jsonobj);
        QByteArray data = jsonDoc.toJson();
        mtcp->write(data);
    //}
}

void post_item::on_pushButton_delete_clicked()//只能点一次
{
    QJsonObject jsonobj;
    jsonobj["msgType"]="DELETE_POST";
    jsonobj["postId"]=postId;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    emit Dynamicupdate();
    emit person_dynamicupdate();
    delete this;
}//重新进入


void post_item::on_pushButton_end_clicked()
{
    QJsonObject jsonobj;
    jsonobj["msgType"]="END_POST";
    jsonobj["postId"]=postId;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    emit Dynamicupdate();
    emit person_dynamicupdate();
//    delete this;
//    Dynamic * w=new Dynamic();
//
}


void post_item::on_pushButton_over_clicked()
{
    QJsonObject jsonobj;
    jsonobj["msgType"]="OVER_POST";
    jsonobj["postId"]=postId;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    emit Dynamicupdate();
    emit person_dynamicupdate();
}

