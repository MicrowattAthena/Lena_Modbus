#include "ec_saloon.h"
#include "ui_ec_saloon.h"
#include "widget.h"
#include "masterdb.h"

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

void EC_Saloon::on_pushButton_released()
{
    Widget *mainwindow = new Widget();
    mainwindow->show();
    this->close();
}


void EC_Saloon::update_ecs_values()
{
    EC_Saloon::getECvalues();
  //  ui->lcd_roomtemp->display
}


void EC_Saloon::getECvalues() {
    int buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,SALOON,REGISTERS,(REG_HUMIDITY - 1));
    ui->lcd_humidity->display(buffer);
}

void EC_Saloon::on_pushButton_2_released()
{
    int buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,SALOON,REGISTERS,(REG_HUMIDITY - 1));
    ui->lcd_humidity->display(buffer);

}
