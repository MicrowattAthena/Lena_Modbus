#include "lcd_display.h"
#include "ui_lcd_display.h"
#include "widget.h"

lcd_display::lcd_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lcd_display)
{
    ui->setupUi(this);
}

lcd_display::~lcd_display()
{
    delete ui;
}

void lcd_display::on_pushButton_released()
{
    Widget *mainwindow = new Widget();
    mainwindow->show();
    this->close();
}

