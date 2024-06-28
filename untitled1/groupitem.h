#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>
#include "my_tcpsocket.h"
namespace Ui {
class groupItem;
}

class groupItem : public QWidget
{
    Q_OBJECT

public:
    explicit groupItem(my_tcpsocket *socket,QJsonObject myInfo_,int groupId_,QString groupName_,QWidget *parent = nullptr);
    int groupId;
    QJsonObject myInfo;
    my_tcpsocket *mtcp;
    QString groupName;
    ~groupItem();

private slots:
    void on_profileButton_clicked();

private:
    Ui::groupItem *ui;

protected:
    void mousePressEvent(QMouseEvent *event)override;
};

#endif // GROUPITEM_H
