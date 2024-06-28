#include "friends.h"
#include "ui_friends.h"

QVBoxLayout* layout0 = new QVBoxLayout;
friends::friends(int a, QString b)
{
    avatar_id = a;
    username = b;

    QPixmap Picture1("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/1.jpg");
    QPixmap Picture2("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/2.jpg");
    QPixmap Picture3("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/3.jpg");
    QPixmap Picture4("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/4.jpg");
    QPixmap Picture5("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/5.jpg");
    QPixmap Picture6("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/6.jpg");
    QPixmap Picture7("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/7.jpg");
    QPixmap Picture8("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/8.jpg");
    QPixmap Picture9("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/9.jpg");
    QPixmap Picture10("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/10.jpg");
    QPixmap Picture11("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/11.jpg");
    QPixmap Picture12("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/12.jpg");
    QPixmap Picture13("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/13.jpg");
    QPixmap Picture14("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/14.jpg");
    QPixmap Picture15("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/15.jpg");
    QPixmap Picture16("C:/Users/祝渐祥/Desktop/Qt/picture/avatar/16.jpg");

    QPixmap Picture[16];
    for(int i=0; i<16; i++){

    }

    Picture1 = Picture1.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture2 = Picture2.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture3 = Picture3.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture4 = Picture4.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture5 = Picture5.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture6 = Picture6.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture7 = Picture7.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture8 = Picture8.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture9 = Picture9.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture10 = Picture10.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture11 = Picture11.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture12 = Picture12.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture13 = Picture13.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture14 = Picture14.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture15 = Picture15.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Picture16 = Picture16.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    switch (avatar_id){
    case 1: avatar->setPixmap(Picture1);break;
    case 2: avatar->setPixmap(Picture2);break;
    case 3: avatar->setPixmap(Picture3);break;
    case 4: avatar->setPixmap(Picture4);break;
    case 5: avatar->setPixmap(Picture5);break;
    case 6: avatar->setPixmap(Picture6);break;
    case 7: avatar->setPixmap(Picture7);break;
    case 8: avatar->setPixmap(Picture8);break;
    case 9: avatar->setPixmap(Picture9);break;
    case 10: avatar->setPixmap(Picture10);break;
    case 11: avatar->setPixmap(Picture11);break;
    case 12: avatar->setPixmap(Picture12);break;
    case 13: avatar->setPixmap(Picture13);break;
    case 14: avatar->setPixmap(Picture14);break;
    case 15: avatar->setPixmap(Picture15);break;
    case 16: avatar->setPixmap(Picture16);break;
    }

    layout->addWidget(avatar);
    layout->addWidget(name);

    layout0->addLayout(layout);
}

friends::~friends()
{
    delete ui;
}
