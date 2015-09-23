#include "ec_bedroom.h"
#include "ui_ec_bedroom.h"
#include "widget.h"

ec_bedroom::ec_bedroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ec_bedroom)
{
    ui->setupUi(this);
}

ec_bedroom::~ec_bedroom()
{
    delete ui;
}

void ec_bedroom::on_pushButton_released()
{
    Widget *mainwindow = new Widget();
    mainwindow->show();
    this->close();
}
