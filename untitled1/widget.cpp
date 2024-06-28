#include "widget.h"
#include "mainwindow.h"
#include "./ui_widget.h"

Widget::Widget(my_tcpsocket *socket, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),mtcp(socket)
{
    ui->setupUi(this);
    //qDebug()<<"连接成功";
    connect(mtcp, &my_tcpsocket::loginMessageReceived, this, &Widget::handleMessage);
    timer=new(QTimer);
    connect(timer,SIGNAL(timeout()),this, SLOT(hide_warningLabel));
    setWindowTitle("搭一搭");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_loginButton_clicked()
{
    QString username=ui->userNameEdit->text();
    QString password=ui->passWordEdit->text();
    //登录信息缺失
    if(username.isEmpty()){
        ui->warningLabel->setText("用户名不能为空");
        timer->start(500);
        return ;
    }
    else if(password.isEmpty()){
        ui->warningLabel->setText("密码不能为空");
        timer->start(500);
        return ;
    }
    //用户名密码匹配
    sendMessage("LOGIN", username, password);
}


void Widget::on_registerButton_clicked()
{
    QString username=ui->userNameEdit->text();
    QString password=ui->passWordEdit->text();
    if(username.isEmpty()){
        ui->warningLabel->setText("用户名不能为空");
        timer->start(500);
        return ;
    }
    else if(password.isEmpty()){
        ui->warningLabel->setText("密码不能为空");
        timer->start(500);
        return ;
    }
    sendMessage("REGISTER", username, password);
}

void Widget::sendMessage(QString msgType, QString username, QString password)
{
    QJsonObject jsonObj;
    jsonObj["msgType"]=msgType;
    jsonObj["username"]=username;
    jsonObj["password"]=password;
    QJsonDocument jsonDoc(jsonObj);
    QByteArray data = jsonDoc.toJson();
    mtcp->write(data);
}

void Widget::sendAvatarMessage(QString msgType, int avatar){
    QJsonObject jsonObj;
    jsonObj["profile"] = avatar;
    QJsonDocument jsonDoc(jsonObj);

}//edited
void Widget::handleMessage(const QJsonObject& jsonObj)
{
    QString msgType=jsonObj.value("msgType").toString();
    QString message=jsonObj.value("msg").toString();
    qDebug()<<msgType<<message;
    if(msgType=="LOGIN"){
        if(message=="success"){
            ui->warningLabel->setText("登陆成功！");

            timer->start(500);
            myUsername=jsonObj.value("username").toString();
            myUserId=jsonObj.value("userId").toInt();

            MainWindow *w = new MainWindow(mtcp, myUserId);
            w->show();//edited
            close();
        }
        else{
            ui->warningLabel->setText("账号或密码错误");
            connect(timer,SIGNAL(timeout()),this, SLOT(hide_warningLabel));
            timer->start(500);
        }
    }
    else{
        if(message=="success"){
            ui->warningLabel->setText("注册成功！");
            timer->start(500);
        }
        else{
            ui->warningLabel->setText("用户名已存在");
            timer->start(500);
        }
    }
}

void Widget::hide_warningLabel(){
    ui->warningLabel->setText("");
}
