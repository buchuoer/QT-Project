#include "person_message.h"
#include "ui_person_message.h"
#include"person_dynamic.h"
person_message::person_message(my_tcpsocket * socket,int userid_,int myid_,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::person_message),mtcp(socket),myid(myid_),userid(userid_)
{
    ui->setupUi(this);
    //冲突;
    QJsonObject jsonobj;
    jsonobj["msgType"]="USERINFO";
    jsonobj["id"]=userid;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    qDebug()<<"写入USERINFO";
    connect(mtcp, &my_tcpsocket::userMessageReceived, this, &person_message::handleMessage);
    setWindowTitle("搭一搭");
}

person_message::~person_message()
{
    delete ui;
}
void person_message::handleMessage(QJsonObject jsonObj){
    qDebug()<<"person_message::handleMessage";
    QString name=jsonObj.value("username").toString();
    int profile=jsonObj.value("profile").toInt();
    int sex=jsonObj.value("sex").toInt();
    QString Sex;
    if(sex==0) Sex="女";
    else if(sex==1) Sex="男";
    QString age=jsonObj.value("age").toString();
//    int bgPhoto=jsonObj.value("bgPhoto").toInt();
    QString imagepath = "://picture/avatar/";
    ui->label_name->setText(name);
    QPixmap pro(imagepath+QString::number(profile)+".jpg");
    qDebug()<<"好友页面头像"<<profile;
    QPixmap pro2=pro.scaled(ui->label_profile->size(),Qt::KeepAspectRatio);
    ui->label_profile->setPixmap(pro2);
    ui->label_age->setText(age);
    ui->label_sex->setText(Sex);
//    QString photobgpath;
//    QString bgPhotopath=photobgpath+QString::number(bgPhoto)+".jpg";bgPhotopath
//    setStyleSheet("QWidget { background-image: url(E:\\dynamic\\image\\2.jpg); }");
}

void person_message::on_pushButton_clicked()
{
    qDebug()<<"person_message::on_pushButton_clicked"<<myid<<userid;
    Person_dynamic * other=new Person_dynamic(myid,userid,mtcp);
    other->show();
}

