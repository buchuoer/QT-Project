#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <QMainWindow>
#include"my_tcpsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dynamic;
}
QT_END_NAMESPACE

class Dynamic : public QMainWindow
{
    Q_OBJECT

public:
    Dynamic(my_tcpsocket * socket,int myid_,QWidget *parent = nullptr);//初始化myid
    void addMessage(const QJsonObject& jsonObj);//,QString name
    ~Dynamic();
private slots:
    void handleMessage(const QJsonObject& jsonObj);
    void on_pushButton_release_clicked();

    void on_pushButton_return_clicked();

    void upDate();

public:
    my_tcpsocket *mtcp;
private:
    Ui::Dynamic *ui;

    int myid;
};
#endif // DYNAMIC_H
