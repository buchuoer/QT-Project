#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"DoubleClickLineEdit.h"
#include "my_tcpsocket.h"
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QFont>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int my_id;
    my_tcpsocket *mtcp;
    int avatar_id;
    int bg_id;
    QString gender_id;
    QString age_id;
    QString name;
    MainWindow(my_tcpsocket *tcp, int userId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleMessage(const QJsonObject& jsonObj);
    void ChangeClicked();
    void ChangebgClicked();
    void ChangenameClicked();
    void ReleaseClicked();
    void PublishedClicked();
    void MineClicked();
    void My_FriendClicked();
    void My_GroupClicked();
    void Add_FriendClicked();
    void Change_GenderClicked();
    void Change_AgeClicked();
    void AddCommitClicked();
    void Todo_Clicked();
private:
    QLabel* Name = new QLabel;
    QLabel* avatar = new QLabel;
    QLabel* gender = new QLabel;
    DoubleClickLineEdit * change_gender = new DoubleClickLineEdit;
    QLabel* age = new QLabel;
    DoubleClickLineEdit * change_age = new DoubleClickLineEdit;
    QVBoxLayout* nga = new QVBoxLayout;
    QHBoxLayout* Age = new QHBoxLayout;
    QHBoxLayout* Gender = new QHBoxLayout;
    QLabel* background = new QLabel;
    QPushButton* changeavatar = new QPushButton;
    QPushButton* changeback = new QPushButton;
    QPushButton* changename = new QPushButton;
    QPushButton* release = new QPushButton;
    QPushButton* published = new QPushButton;
    QPushButton* mine = new QPushButton;
    QPushButton* my_friend = new QPushButton;
    QPushButton* my_group = new QPushButton;
    QPushButton* add_friend = new QPushButton;
    QPushButton* todoList = new QPushButton;
    QWidget *w = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* layout0 = new QHBoxLayout;
    QFont font;
    QJsonObject myInfo;
    QPushButton* addcommit = new QPushButton;
    QLineEdit* addfriend = new QLineEdit;
    QWidget* addw = new QWidget;


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
