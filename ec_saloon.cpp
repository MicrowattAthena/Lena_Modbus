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
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
  QObject::connect(handler,SIGNAL(requestupdate()),this,SLOT(update_ecs_values()));

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
     qWarning() << buffer;
      qWarning() << "Updating Humidity Value";
    ui->lcd_humidity->display(buffer);
}






void EC_Saloon::on_horizontalSlider_2_sliderReleased()
{
    int buffer;
    buffer = ui->horizontalSlider_2->value();



}
