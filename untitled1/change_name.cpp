#include "change_name.h"
#include "mainwindow.h"

change_name::change_name(my_tcpsocket *tcp, int userId, QWidget *parent)
    : QWidget(parent)
{
    mtcp = tcp;
    my_id = userId;

    connect(commit, &QPushButton::clicked, this, &change_name::CommitClicked);

    commit->setText("确   认");
    layout->addWidget(tip);
    layout->addWidget(new_name);
    layout->addWidget(commit);
    changenamew->setLayout(layout);

}
void change_name::CommitClicked(){
    QJsonObject jsonObj;
    jsonObj["msgType"]="UPDATE_BGPHOTO";
    jsonObj["id"]=my_id;
    jsonObj["serial"]=1;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);




    QMessageBox::information(this, "提示", "设置成功!");
    QString input = new_name->text();
    new_name->clear();
    changenamew->hide();
    MainWindow *w = new MainWindow(mtcp, my_id);
    w->show();
}

change_name::~change_name()
{

}
