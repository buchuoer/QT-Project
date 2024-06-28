#ifndef WIDGET_H
#define WIDGET_H
# include <QThread>
#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include "chat_window.h"
#include "my_tcpsocket.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(my_tcpsocket *socket, QWidget *parent=nullptr);
    void sendMessage(QString msgType, QString username, QString password);
    void sendAvatarMessage(QString msgType, int avatar);//edited
    ~Widget();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void handleMessage(const QJsonObject& jsonObj);
    void hide_warningLabel();

private:
    Ui::Widget *ui;
    my_tcpsocket* mtcp;
    QTimer* timer;//定时器
    QString myUsername="";
    int myAvatarId;
    int myBackgroundId;
    QString friendUsername="";
    int myUserId=0;
    int profile=1;
    //int sum=1;

};
#endif // WIDGET_H
