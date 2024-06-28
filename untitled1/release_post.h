#ifndef RELEASE_POST_H
#define RELEASE_POST_H
#include "my_tcpsocket.h"
#include <QWidget>

namespace Ui {
class release_post;
}

class release_post : public QWidget
{
    Q_OBJECT

public:
    explicit release_post(my_tcpsocket * socket,int myid_,QWidget *parent = nullptr);
    ~release_post();

signals:
    void back();

private slots:
    void on_pushButton_release_clicked();

    void on_pushButton_cancel_clicked();

    void handleMessage(const QJsonObject& jsonObj);

public:
    int myid;
private:
    Ui::release_post *ui;
    my_tcpsocket * mtcp;
};

#endif // RELEASE_POST_H
