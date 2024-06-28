#include "messageitem.h"
#include "ui_messageitem.h"

MessageItem::MessageItem(const int profile_,const QString &senderName_, const QString &message_,const QString &timestamp_, QWidget * parent)
    :profile(profile_),senderName(senderName_),messageText(message_),QWidget(parent),timestamp(timestamp_)
    , ui(new Ui::MessageItem)
{
    ui->setupUi(this);
    QPixmap pro("://picture/avatar/"+QString::number(profile)+".jpg");
    QPixmap pro2=pro.scaled(ui->profileText->size(),Qt::KeepAspectRatio);
    ui->profileText->setPixmap(pro2);
    ui->usernameText->setText(senderName);
    qDebug()<<messageText;
    ui->msgText->setText(messageText);

    qDebug()<<timestamp;
    ui->timeText->setText(timestamp);
}

MessageItem::~MessageItem()
{
    delete ui;
}

