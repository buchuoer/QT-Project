#include "groupitem.h"
#include "ui_groupitem.h"
#include "chat_window.h"
groupItem::groupItem(my_tcpsocket *socket,QJsonObject myInfo_,int groupId_,QString groupName_,QWidget *parent )
    : QWidget(parent),groupId(groupId_),groupName(groupName_),mtcp(socket),myInfo(myInfo_)
    , ui(new Ui::groupItem)
{
    ui->setupUi(this);
    ui->groupNameText->setText(groupName);
    QString imagepath="://picture/group/";   //:/image/1.jpg
    QPixmap pro(imagepath+QString::number(1)+".jpg");
    QIcon buttonIcon(pro);
    ui->profileButton->setIcon(buttonIcon);//头像设置
    ui->profileButton->setIconSize({31,31});

}

void groupItem::mousePressEvent(QMouseEvent *event){
    QString myName=myInfo.value("username").toString();
    int myProfile = myInfo.value("profile").toInt();
    int myId = myInfo.value("userId").toInt();
    chat_window* w = new chat_window(mtcp,groupId,groupName,myId,myName,myProfile);//待释放
    w->show();
    QWidget::mousePressEvent(event);
}


groupItem::~groupItem()
{
    delete ui;
}

void groupItem::on_profileButton_clicked()
{
    //待写
}

