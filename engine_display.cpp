#include "engine_display.h"
#include "ui_engine_display.h"
#include "masterdb.h"
#include "guihandler.h"
#include "widget.h"
#include "main.h"
#include "General/general_registers.h"

#include <QDebug>
extern guihandler *handler;


engine_display::engine_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::engine_display)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
    QObject::connect(handler,SIGNAL(requestupdate()),this,SLOT(update_engine_values()));
    update_engine_values();
}

engine_display::~engine_display()
{
    delete ui;
}

void engine_display::on_pushButton_released()
{
    Widget *mainwindow = new Widget();
    mainwindow->show();
    this->close();
}

void engine_display::update_engine_values()
{
    //FIRST THIS NEEDS TO WRITE ANY QUEUED CHANGES TO THE DB. THEN, READ FROM DB TO GUI.

    int buffer;
    qWarning() << "Updating Engine Management";

    //Battery Tab
    buffer = get_databasevalues(REG_ANALOG_IN12,REGISTERS);
    ui->display_V_servicebattery->display(buffer);
    buffer = get_databasevalues(REG_ANALOG_IN13,REGISTERS);
    ui->display_V_starterbattery->display(buffer);
    buffer = get_databasevalues(REG_ANALOG_IN14,REGISTERS);
    ui->display_V_otherbattery->display(buffer);
    buffer = get_databasevalues(REG_ANALOG_IN15,REGISTERS);
    ui->display_A_servicebattery->display(buffer);
    buffer = get_databasevalues(REG_BAT_FSD,REGISTERS);
    ui->control_batterycurrentfsd->setValue(buffer);


    //Engine Limits Tab
    buffer = get_databasevalues(REG_ENG_VTHRESH1,REGISTERS);
    ui->control_V_enginethresh_1->setValue(buffer);
    buffer = get_databasevalues(REG_ENG_VTHRESH2,REGISTERS);
    ui->control_V_Enginethresh_2->setValue(buffer);
    buffer = get_databasevalues(REG_ENG_CURRTHR,REGISTERS);
    ui->Control_A_EngineThresh->setValue(buffer);


    //Engine Controls Tab
    buffer = get_databasevalues(REG_GEN_ENG_MODE,REGISTERS);
    ui->control_enginemode->setValue(buffer);
    buffer = get_databasevalues(REG_ENG_RPM,REGISTERS);
    ui->display_engineRPM->display(buffer);


    //Heating Tab
    buffer = get_databasevalues(REG_HEATING_MODE,REGISTERS);
    ui->control_heatingmode->setValue(buffer);
    buffer = get_databasevalues(REG_HEATING_THRESH,REGISTERS);
    ui->control_heatingthresh->setValue(buffer);


    //Coils Tab
    buffer = get_databasevalues(COIL_INPUT1,COILS);
    ui->chk_Input1->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT2,COILS);
    ui->chk_input2->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT3,COILS);
    ui->chk_input3->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT4,COILS);
    ui->chk_input4->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT5,COILS);
    ui->chk_input5->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT6,COILS);
    ui->chk_input6->setChecked(buffer);
    buffer = get_databasevalues(COIL_INPUT7,COILS);
    ui->chk_input7->setChecked(buffer);

    buffer = get_databasevalues(COIL_OUTPUT1,COILS);
    ui->chk_output1->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT2,COILS);
    ui->chk_output2->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT3,COILS);
    ui->chk_output3->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT4,COILS);
    ui->chk_output4->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT5,COILS);
    ui->chk_output5->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT6,COILS);
    ui->chk_output6->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT7,COILS);
    ui->chk_output7->setChecked(buffer);
    buffer = get_databasevalues(COIL_OUTPUT8,COILS);
    ui->chk_output8->setChecked(buffer);
}

float engine_display::get_databasevalues(int REGISTER_LOCATION, char INPUTTYPE)
{

    /*Gets the value from the DB */

    float buffer;
    buffer = senddatatoGUI(GENERAL_BOARD,GENERAL_ENGINE,INPUTTYPE,REGISTER_LOCATION);
    return buffer;

}

void engine_display::checkuserinput(char slavetype, char slavename, char addresstype, int registerlocation, int value)
{
    int buffer;

    //Measurement Tab
    buffer = get_databasevalues(registerlocation,addresstype);
    if (buffer == value){
       //        qWarning() << "NOT USER UPDATED!";
    }else{
        getqueuedata(slavetype,slavename, addresstype, registerlocation, value);
    }

}

void engine_display::on_control_batterycurrentfsd_valueChanged(int value)
{
    ui->label_batterycurrentfsd->setText(QString::number(value) + " A");
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_BAT_FSD,value);
}

void engine_display::on_control_V_enginethresh_1_valueChanged(int value)
{
    ui->label_engine_v_thresh1->setText(QString::number(value) + " V");
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_ENG_VTHRESH1,value);
}

void engine_display::on_control_V_Enginethresh_2_valueChanged(int value)
{
    ui->label_engine_v_thresh2->setText(QString::number(value) + " V");
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_ENG_VTHRESH2,value);
}

void engine_display::on_Control_A_EngineThresh_valueChanged(int value)
{
    ui->label_engine_athresh->setText(QString::number(value) + " A");
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_ENG_CURRTHR,value);
}

void engine_display::on_control_enginemode_valueChanged(int value)
{
    QString modes[4];
    modes[0] = "Read from\nPins";
    modes[1] = "On";
    modes[2] = "Off";
    modes[3] = "Auto";

    ui->label_enginemode->setText(modes[value]);
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG__EC_ENG_MODE,value);
}


void engine_display::on_control_heatingmode_valueChanged(int value)
{
    QString modes[4];
    modes[0] = "Read from\nPins";
    modes[1] = "On";
    modes[2] = "Off";
    modes[3] = "Auto";

    ui->label_heatingmode->setText(modes[value]);
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_HEAT_MODE,value);
}

void engine_display::on_control_heatingthresh_valueChanged(int value)
{

    ui->label_heatingthresh->setText(QString::number(value) + " degreesC");
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_HEATING_THRESH,value);
}

void engine_display::on_chk_Input1_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT1,arg1);

}

void engine_display::on_chk_input2_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT2,arg1);

}

void engine_display::on_chk_input3_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT3,arg1);

}

void engine_display::on_chk_input4_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT4,arg1);

}

void engine_display::on_chk_input5_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT5,arg1);

}



void engine_display::on_chk_input6_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT6,arg1);

}

void engine_display::on_chk_input7_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_INPUT7,arg1);

}

void engine_display::on_chk_output1_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT1,arg1);

}

void engine_display::on_chk_output2_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT2,arg1);
}

void engine_display::on_chk_output3_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT3,arg1);
}

void engine_display::on_chk_output4_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT4,arg1);
}

void engine_display::on_chk_output5_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT5,arg1);
}

void engine_display::on_chk_output6_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT6,arg1);
}

void engine_display::on_chk_output7_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT7,arg1);
}

void engine_display::on_chk_output8_stateChanged(int arg1)
{
    if (arg1) {
        arg1 = 1;
    }
    checkuserinput(GENERAL_BOARD,GENERAL_ENGINE,COILS,COIL_OUTPUT8,arg1);
}
