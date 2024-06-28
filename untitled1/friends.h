#ifndef FRIENDS_H
#define FRIENDS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class friends;
}

class friends : public QWidget
{
    Q_OBJECT

public:
    friends(int a, QString b);
    ~friends();

private:
    int avatar_id;
    QString username;
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* avatar = new QLabel;
    QLabel* name = new QLabel(username);

    Ui::friends *ui;
};

#endif // FRIENDS_H
