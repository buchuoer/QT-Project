#ifndef PERSON_MESSAGE_H
#define PERSON_MESSAGE_H

#include <QWidget>
#include "my_tcpsocket.h"
namespace Ui {
class person_message;
}

class person_message : public QWidget
{
    Q_OBJECT

public:
    explicit person_message(my_tcpsocket * socket,int userid_,int myid_,QWidget *parent = nullptr);
    ~person_message();
private slots:
    void handleMessage(QJsonObject jsonObj);
    void on_pushButton_clicked();

private:
    Ui::person_message *ui;
    my_tcpsocket * mtcp;
    int userid;
    int myid;
};

#endif // PERSON_MESSAGE_H
