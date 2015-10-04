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
    qWarning() << "Updating EC-Saloon";

    //Measurement Tab
    buffer = get_databasevalues(REG_HUMIDITY);
    ui->display_humidity->display(buffer);

    buffer = get_databasevalues(REG_TEMPR_ROOM);
    ui->display_roomtemp->display(buffer);

    buffer = get_databasevalues(REG_TEMPR_WATERFLOW);
    ui->display_watertemp->display(buffer);

    buffer = get_databasevalues(REG_CO2_PPM);
    ui->display_co2->display(buffer);

    buffer = get_databasevalues(REG_LCD_BRIGHTNESS);
    ui->display_LCDbrightness->display(buffer);


}

float EC_Saloon::get_databasevalues(int REGISTER_LOCATION)
{

    /*Gets the value from the DB and then applies the correct multiplier to display the 'real value'. E.G. Temperatures
    /Must be divided by 10 */

    int buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,SALOON,REGISTERS,REGISTER_LOCATION);
    buffer = buffer / ECMultipliers[REGISTER_LOCATION];
    return buffer;

}
