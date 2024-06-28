#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QWidget>

namespace Ui {
class MessageItem;
}

class MessageItem : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItem(const int profile_,const QString &senderName_, const QString &message_,const QString &timestamp_, QWidget *parent = nullptr);
    ~MessageItem();

private:
    Ui::MessageItem *ui;
    QString senderName;
    int profile;
    QString messageText;
    QString timestamp;
};

#endif // MESSAGEITEM_H
