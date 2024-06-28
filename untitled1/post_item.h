#ifndef POST_ITEM_H
#define POST_ITEM_H

#include <QWidget>
#include "my_tcpsocket.h"
namespace Ui {
class post_item;
}

class post_item : public QWidget
{
    Q_OBJECT

public:
    explicit post_item(int myid_,int senderid_,my_tcpsocket * socket,QWidget *parent = nullptr);
    ~post_item();

    void setDate(const QJsonObject& jsonObj);//,QString name

private slots:
    void on_pushButton_user_clicked();

    void on_pushButton_join_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_end_clicked();

    void on_pushButton_over_clicked();
signals:
    void Dynamicupdate();
    void person_dynamicupdate();
public:
    int senderid;
    int postId;
    int myid;
private:
    Ui::post_item *ui;
    my_tcpsocket * mtcp;
};

#endif // POST_ITEM_H
