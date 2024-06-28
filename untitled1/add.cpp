#include "add.h"
#include "ui_add.h"

add::add(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add)
{
    ui->setupUi(this);
}

add::~add()
{
    delete ui;
}
