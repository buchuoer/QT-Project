#ifndef PENDINGMESSAGEITEM_H
#define PENDINGMESSAGEITEM_H

#include <QWidget>

namespace Ui {
class pendingmessageitem;
}

class pendingmessageitem : public QWidget
{
    Q_OBJECT

public:
    explicit pendingmessageitem(QWidget *parent = nullptr);
    ~pendingmessageitem();

private:
    Ui::pendingmessageitem *ui;
};

#endif // PENDINGMESSAGEITEM_H
