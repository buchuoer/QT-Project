#ifndef MY_TCPSOCKET_H
#define MY_TCPSOCKET_H

#include <QQuickItem>
#include <QSharedDataPointer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
//#include<QAbstractSocket>
QT_BEGIN_NAMESPACE
class my_tcpsocketData;

class my_tcpsocket :public QTcpSocket
{
    Q_OBJECT
public:
    my_tcpsocket(QHostAddress hostAddress, int port, QObject *parent = nullptr);
    //my_tcpsocket(const my_tcpsocket &);
    my_tcpsocket &operator=(const my_tcpsocket &);
    ~my_tcpsocket();

signals:
    void loginMessageReceived(const QJsonObject& jsonObj); // 登录相关的消息
    void chatMessageReceived(const QJsonObject& jsonObj); // 聊天相关的消息
    void MyInfoReceived(const QJsonObject& jsonObj);
    void onlinepostMessageReceived(const QJsonObject& JsonObj);
    void userMessageReceived(const QJsonObject& JsonObj);
    void userpostMessageReceived(const QJsonObject& JsonObj);
    void MessageReceived(const QJsonObject& JsonObj);
    void ListMessageReceived(const QJsonObject& JsonObj);//列表信息

public slots:
    void handleReadyRead();

private:
    //QSharedDataPointer<my_tcpsocketData> data;
};

#endif // MY_TCPSOCKET_H
