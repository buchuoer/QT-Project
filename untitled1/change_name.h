#ifndef CHANGE_NAME_H
#define CHANGE_NAME_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class change_name;
}

class change_name : public QWidget
{
    Q_OBJECT

public:
    change_name(my_tcpsocket *tcp, int userId, QWidget *parent = nullptr);
    ~change_name();
    void Show(){
        changenamew->show();
    }

private slots:
    void CommitClicked();

private:
    QLabel* tip = new QLabel("请输入您的年龄");
    QLineEdit* new_name = new QLineEdit;
    QVBoxLayout* layout = new QVBoxLayout;
    QWidget* changenamew = new QWidget;
    QPushButton* commit = new QPushButton;

    my_tcpsocket* mtcp;
    int my_id;

    Ui::change_name *ui;
};

#endif // CHANGE_NAME_H
