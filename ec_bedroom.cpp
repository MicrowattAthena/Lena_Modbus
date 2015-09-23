#include "ec_bedroom.h"
#include "ui_ec_bedroom.h"

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
