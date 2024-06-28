#ifndef TODOITEM_H
#define TODOITEM_H

#include <QWidget>
# include "my_tcpsocket.h"
namespace Ui {
class todoItem;
}

class todoItem : public QWidget
{
    Q_OBJECT

public:
    my_tcpsocket * mtcp;
    QJsonObject msgObj;
    todoItem(my_tcpsocket * socket,const QJsonObject & msgObj_ , QWidget *parent = nullptr);
    ~todoItem();

private slots:
    void on_agreeButton_clicked();

    void on_disagreeButton_clicked();

private:
    Ui::todoItem *ui;
};

#endif // TODOITEM_H
