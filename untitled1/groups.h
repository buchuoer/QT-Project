#ifndef GROUPS_H
#define GROUPS_H

#include <QWidget>

namespace Ui {
class groups;
}

class groups : public QWidget
{
    Q_OBJECT

public:
    explicit groups(QWidget *parent = nullptr);
    ~groups();

private:
    Ui::groups *ui;
};

#endif // GROUPS_H
