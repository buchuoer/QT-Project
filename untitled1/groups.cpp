#include "groups.h"
#include "ui_groups.h"

groups::groups(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::groups)
{
    ui->setupUi(this);
}

groups::~groups()
{
    delete ui;
}
