#ifndef PERSON_DYNAMIC_H
#define PERSON_DYNAMIC_H

#include <QMainWindow>
#include"my_tcpsocket.h"
namespace Ui {
class Person_dynamic;
}

class Person_dynamic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Person_dynamic(int myid_,int hostid_,my_tcpsocket * socket,QWidget *parent = nullptr);
    ~Person_dynamic();
    void addMessage(const QJsonObject& jsonObj);//,QString name
private slots:
    void handleMessage(const QJsonObject& jsonObj);
private:
    Ui::Person_dynamic *ui;
    int myid;
    my_tcpsocket *mtcp;
    int hostid;
};

#endif // PERSON_DYNAMIC_H
