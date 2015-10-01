#include "widget.h"
#include "ui_widget.h"
#include "ec_bedroom.h"
#include "ec_saloon.h"
#include "lcd_display.h"
#include "engine_display.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setGeometry(0,0,800,480);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_btn_ECBedroom_released()
{
    ec_bedroom *testwindow = new ec_bedroom();
    testwindow->show();
    this->close();
}

void Widget::on_btn_ECSaloon_released()
{
    EC_Saloon *testwindow = new EC_Saloon();
    testwindow->show();
    this->close();
}

void Widget::on_btn_LCD_released()
{
    lcd_display *testwindow = new lcd_display();
    testwindow->show();
    this->close();
}

void Widget::on_btn_Engine_released()
{
    engine_display *testwindow = new engine_display();
    testwindow->show();
    this->close();
}

void Widget::on_pushButton_released()
{
    EC_Saloon *testwindow = new EC_Saloon();
    testwindow->show();
    this->close();
}
