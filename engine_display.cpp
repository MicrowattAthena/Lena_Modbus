#include "engine_display.h"
#include "ui_engine_display.h"
#include "widget.h"

engine_display::engine_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::engine_display)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
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
