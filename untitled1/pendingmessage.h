#ifndef PENDINGMESSAGE_H
#define PENDINGMESSAGE_H
#include "my_tcpsocket.h"
#include <QWidget>

namespace Ui {
class pendingmessage;
}

class pendingmessage : public QWidget
{
    Q_OBJECT

public:
    my_tcpsocket * mtcp;
    QString type;
    QJsonObject myInfo;
    explicit pendingmessage(my_tcpsocket * socket, QJsonObject myInfo_, QString type, QWidget *parent = nullptr);
    void addMessage( QJsonObject myInfo,int Id,QString Name,int profile);//添加好友
    void addMessage( QJsonObject myInfo,int Id,QString Name);//添加
    void addMessage(const QJsonObject & msgObj);//添加待办消息
private:

    ~pendingmessage();
    Ui::pendingmessage *ui;
private  slots:
    void handleMessage(const QJsonObject & jsonObj);

};

#endif // PENDINGMESSAGE_H
