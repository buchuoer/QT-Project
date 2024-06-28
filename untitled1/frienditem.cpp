#include "frienditem.h"
#include "ui_frienditem.h"
#include "chat_window.h"
friendItem::friendItem(my_tcpsocket * socket,QJsonObject myInfo_,int userId_,QString userName_,int profile_,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::friendItem),userId(userId_),userName(userName_),profile(profile_),mtcp(socket),myInfo(myInfo_)
{
    ui->setupUi(this);
    QString imagepath="://picture/avatar/";   //:/image/1.jpg
    //QPixmap pro(imagepath+QString::number(profile)+".jpg");
    //qDebug()<<imagepath+QString::number(profile)+".jpg";
    //QPixmap pro2=pro.scaled(ui->profileButton->size(),Qt::KeepAspectRatio);
    QIcon buttonIcon(imagepath+QString::number(profile)+".jpg");
    ui->profileButton->setIcon(buttonIcon);//头像设置
    ui->profileButton->setIconSize({31,31});
    ui->usernameText->setText(userName);

}

friendItem::~friendItem()
{
    delete ui;
}

void friendItem::mousePressEvent(QMouseEvent *event){
    QString myName=myInfo.value("username").toString();
    int myProfile = myInfo.value("profile").toInt();
    int myId = myInfo.value("userId").toInt();
    chat_window* w = new chat_window(mtcp,userId,userName,profile,myId,myName,myProfile);//待释放
    w->show();
    QWidget::mousePressEvent(event);
}



void friendItem::on_profileButton_clicked()
{
    int myId = myInfo.value("userId").toInt();
    person_message* w = new person_message(mtcp,userId,myId);//待释放
    w->show();
}

