#include "widget.h"
#include "my_tcpsocket.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "log_on_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    my_tcpsocket* mtcp1=new my_tcpsocket(QHostAddress("127.0.0.1"), 12345);
    Widget w1(mtcp1);
    w1.show();
    my_tcpsocket* mtcp2=new my_tcpsocket(QHostAddress("127.0.0.1"), 12345);
    Widget w2(mtcp2);
    w2.show();
    my_tcpsocket* mtcp3=new my_tcpsocket(QHostAddress("127.0.0.1"), 12345);
    Widget w3(mtcp3);
    w3.show();
    my_tcpsocket* mtcp4=new my_tcpsocket(QHostAddress("127.0.0.1"), 12345);
    Widget w4(mtcp4);
    w4.show();

    return a.exec();
}
