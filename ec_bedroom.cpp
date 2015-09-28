#include "ec_bedroom.h"
#include "ui_ec_bedroom.h"
#include "widget.h"
#include "masterdb.h"
int testvalue = 10;
ec_bedroom::ec_bedroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ec_bedroom)
{
    ui->setupUi(this);
    ui->lcdNumber->display(testvalue);
    ui->horizontalSlider->setValue(testvalue);
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

