#include "ec_saloon.h"
#include "ui_ec_saloon.h"

EC_Saloon::EC_Saloon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EC_Saloon)
{
    ui->setupUi(this);
}

EC_Saloon::~EC_Saloon()
{
    delete ui;
}
