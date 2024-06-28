#ifndef FRIENDITEM_H
#define FRIENDITEM_H
# include "my_tcpsocket.h"
#include "person_message.h"
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class friendItem;
}

class friendItem : public QWidget
{
    Q_OBJECT

public:
    explicit friendItem(my_tcpsocket * socket,QJsonObject myINfo_,int userId_,QString userName_,int profile_,QWidget *parent = nullptr);
    int userId;
    QString userName;
    QJsonObject myInfo;
    my_tcpsocket * mtcp;
    int profile;
    ~friendItem();

private slots:
    //void showinfo();

    void on_profileButton_clicked();

private:
    Ui::friendItem *ui;

protected:
    void mousePressEvent(QMouseEvent *event)override;

};

#endif // FRIENDITEM_H
