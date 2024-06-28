#include "release_post.h"
#include "ui_release_post.h"
//#include "dynamic.h"
#include <QDateTime>
#include<QJsonObject>
#include<QJsonDocument>

release_post::release_post(my_tcpsocket * socket,int myid_,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::release_post),mtcp(socket),myid(myid_)
{
    ui->setupUi(this);
    this->setWindowTitle("发布动态编辑界面");
    QString imagepath="://picture/avatar/";
    //此处是否要和服务器连接
    QJsonObject jsonobj;
    jsonobj["msgType"]="USERINFO";
    jsonobj["id"]=myid;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
    connect(mtcp, &my_tcpsocket::userMessageReceived, this, &release_post::handleMessage);
    //  ui->pushButton_user->setStyle("QPushButton { border: none; background-image: url(" + imagePath + QString::number(id)+".jpg"+"); }");
    //  ui->label_pic->setStyleSheet("image: url(:/Image/myself.jpg);");
    QPixmap pro(imagepath+QString::number(2)+".jpg");
    QPixmap pro2=pro.scaled(ui->label_pic->size(),Qt::KeepAspectRatio);
    ui->label_pic->setPixmap(pro2);
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString str = dateTime .toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    ui->label_time->setText(str);
    setWindowTitle("搭一搭");
}

release_post::~release_post()
{
    delete ui;
}

void release_post::on_pushButton_release_clicked()//更新数据到数据库同步到发布页面
{
    QJsonObject jsonobj;
    jsonobj["msgType"]="PUBLISH_POST";
    jsonobj["content"]=ui->textEdit->toPlainText();
    jsonobj["kind"]=ui->comboBox_type->currentText();
    //人数
    //
    qDebug()<<ui->comboBox_type->currentText();
    qDebug()<<ui->textEdit->toPlainText();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("M/d/yy  hh:mm");
    jsonobj["timestamp"]=formattedDateTime;
    qDebug()<<formattedDateTime;
    QJsonDocument jsonDoc(jsonobj);
    QByteArray data = jsonDoc.toJson();
    qDebug()<<"成功写入";
    mtcp->write(data);
    //将两个界面都要更新，个人界面和搭子大厅界面
    //返回大厅
    this->close();
    emit back();
//    mtcp->messageTypewrite("ONLINE_POSTS");

//    mtcp->messageTypewrite("My_POSTS");
}

void release_post::handleMessage(const QJsonObject& jsonObj){//读取头像，
        QString name=jsonObj.value("username").toString();
        ui->label_name->setText(name);
        //图片；
        int profile=jsonObj.value("profile").toInt();
        QString imagepath="://picture/avatar/";
        QPixmap pro(imagepath+QString::number(profile)+".jpg");
        QPixmap pro2=pro.scaled(ui->label_pic->size(),Qt::KeepAspectRatio);
        ui->label_pic->setPixmap(pro2);
}
void release_post::on_pushButton_cancel_clicked()
{
    this->close();
    emit back();
}
//关掉release_post不会返回上一级窗口
