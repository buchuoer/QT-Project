#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QWidget>
#include "messageitem.h"
#include "my_tcpsocket.h"
namespace Ui {
class chat_window;
}

class chat_window : public QWidget
{
    Q_OBJECT

public:
    explicit chat_window(my_tcpsocket * socket, int firendId_,QString friendName, int fdProfile,
                         int myId, QString myName, int myProfile, QWidget *parent = nullptr);
    chat_window(my_tcpsocket * socket,int groupId_,
                QString groupName_,int myId_, QString myName_, int myProfile_,QWidget *parent = nullptr);
    void addMessage(const QString &senderName,int profile, const QString &messageconst ,const QString &timestamp);
    ~chat_window();

private slots:
    void on_msgSendButton_released();
    void handleMessage(const QJsonObject& jsonObj);

    void on_msgEdit_returnPressed();

   // void on_msglist_itemPressed(QListWidgetItem *item);

private:
    Ui::chat_window *ui;
    my_tcpsocket *mtcp;
    int friendId=0;
    int myId;
    QString friendName="";
    QString myName;
    int fdProfile=0;
    int myProfile;
    int groupId=0;
    QString groupName="";
};

#endif // CHAT_WINDOW_H
