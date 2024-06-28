#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
# include "Database.h"
class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
   // ~Server();

private slots:
    void newConnection();
    //void disConnection();
    void readyRead();

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket *> clients;
    UserDatabase* db;
    QMap<QTcpSocket*, int> connectedClients;
    QMap<int,QTcpSocket*> connectedUser;
};

#endif // SERVER_H
