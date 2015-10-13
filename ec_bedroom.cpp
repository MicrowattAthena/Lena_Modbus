#include "ec_bedroom.h"
#include "ui_ec_bedroom.h"
#include "widget.h"
#include "masterdb.h"
#include "guihandler.h"
#include "main.h"

#include <QDebug>

extern guihandler *handler;

ec_bedroom::ec_bedroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ec_bedroom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
    QObject::connect(handler,SIGNAL(requestupdate()),this,SLOT(update_ecb_values()));
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


void ec_bedroom::update_ecb_values()
{
    //FIRST THIS NEEDS TO WRITE ANY QUEUED CHANGES TO THE DB. THEN, READ FROM DB TO GUI.

    int buffer;
    qWarning() << "Updating EC-Bedroom";

    //Measurement Tab
    buffer = get_databasevalues(REG_HUMIDITY);
    ui->display_humidity->display(buffer);
    buffer = get_databasevalues(REG_TEMPR_ROOM);
    ui->display_roomtemp->display(buffer);
    buffer = get_databasevalues(REG_TEMPR_WATERFLOW);
    ui->display_watertemp->display(buffer);
    buffer = get_databasevalues(REG_CO2_PPM);
    ui->display_co2->display(buffer);
    buffer = get_databasevalues(REG_TEMPR_AIRIN);
    ui->display_airintemp->display(buffer);
    buffer = get_databasevalues(REG_TEMPR_AIROUT);
    ui->display_airouttemp->display(buffer);

    //Threshold Tab
    buffer = get_databasevalues(REG_ROOM_TEMPR_THRESH);
    ui->control_roomtemp->setValue(buffer);
    buffer = get_databasevalues(REG_FLOW_TEMPR_THRESH);
    ui->control_watertemp->setValue(buffer);
    buffer = get_databasevalues(REG_HUMIHI_THRESH);
    ui->control_highhumidity->setValue(buffer);
    buffer = get_databasevalues(REG_HUMILO_THRESH);
    ui->control_lowhumidity->setValue(buffer);
    buffer = get_databasevalues(REG_CO2ALRM_THRESH);
    ui->control_co2limit->setValue(buffer);

    //Board Control Tab
    buffer = get_databasevalues(REG_LCD_BRIGHTNESS);
    ui->control_backlightbrightness->setValue(buffer);
    buffer = get_databasevalues(REG_BLIGHT_TIMEOUT);
    ui->control_blight->setValue(buffer);
    buffer= get_databasevalues(REG_TEMPLED_TOLER);
    ui->control_ledtolerance->setValue(buffer);
}

float ec_bedroom::get_databasevalues(int REGISTER_LOCATION)
{

    /*Gets the value from the DB and then applies the correct multiplier to display the 'real value'. E.G. Temperatures
    /Must be divided by 10 */

    float buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,BEDROOM,REGISTERS,REGISTER_LOCATION);
    buffer = buffer / ECMultipliers[REGISTER_LOCATION];
    return buffer;

}
void ec_bedroom::checkuserinput(char slavetype, char slavename, char addresstype, int registerlocation, int value){
    int buffer;
    int buffer2;
    qWarning() << "CHECKING IF USER UPDATED";

    //Measurement Tab
    buffer = get_databasevalues(registerlocation);
    qWarning() << buffer;
      qWarning() << value;
    if (buffer == value){
               qWarning() << "NOT USER UPDATED!";
    }else{
         qWarning() << "USER UPDATED!";
         value = value * ECMultipliers[registerlocation];
        getqueuedata(slavetype,slavename, addresstype, registerlocation, value);
    }

}

void ec_bedroom::on_control_roomtemp_valueChanged(int value)
{
    ui->control_displayroomtemp->setText(QString::number(value));
    checkuserinput(ENVIRONMENTAL_CONTROL,BEDROOM,REGISTERS,REG_ROOM_TEMPR_THRESH,value);

}

void ec_bedroom::on_control_highhumidity_valueChanged(int value)
{
    ui->control_displayhighhumidity->setText(QString::number(value));
}

void ec_bedroom::on_control_lowhumidity_valueChanged(int value)
{
    ui->control_displaylowhumidity->setText(QString::number(value));
}

void ec_bedroom::on_control_co2limit_valueChanged(int value)
{
    ui->control_displayco2limit->setText(QString::number(value));
}

void ec_bedroom::on_control_backlightbrightness_valueChanged(int value)
{
    ui->control_displaybacklightbrightness->setText(QString::number(value));
}

void ec_bedroom::on_control_ledtolerance_valueChanged(int value)
{
    ui->control_displayledtolerance->setText(QString::number(value));
}

void ec_bedroom::on_control_blight_valueChanged(int value)
{
    ui->control_displayblight->setText(QString::number(value));
}


void ec_bedroom::on_control_watertemp_valueChanged(int value)
{
    ui->control_displaywatertemp->setText(QString::number(value));
}



void ec_bedroom::on_control_roomtemp_sliderReleased()
{


}
