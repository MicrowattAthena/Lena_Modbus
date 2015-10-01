#include "ec_bedroom.h"
#include "ui_ec_bedroom.h"
#include "widget.h"
#include "masterdb.h"
#include "guihandler.h"
#include "main.h"

extern guihandler *handler;

ec_bedroom::ec_bedroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ec_bedroom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
    // QObject::connect(handler,&guihandler::requestupdate, this,&ec_bedroom ::update_ecb_values);
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
    int buffer;
    buffer = senddatatoGUI(ENVIRONMENTAL_CONTROL,BEDROOM,REGISTERS,(REG_HUMIDITY));
    ui->enc_b_humidity_lbl->setText(QString::number(buffer));

}
