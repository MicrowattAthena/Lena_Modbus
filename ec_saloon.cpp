#include "ec_saloon.h"
#include "ui_ec_saloon.h"
#include "widget.h"
#include "guihandler.h"
#include "masterdb.h"
#include "main.h"
#include <QDebug>

extern guihandler *handler;
EC_Saloon::EC_Saloon(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::EC_Saloon)
{
    ui->setupUi(this);

  //QObject::connect(handler,&guihandler::requestupdate, this,&EC_Saloon ::update_ecs_values);

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
    int buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,SALOON,REGISTERS,(REG_HUMIDITY));
    ui->lcd_humidity->display(buffer);
}





