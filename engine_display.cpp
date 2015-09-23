#include "engine_display.h"
#include "ui_engine_display.h"

engine_display::engine_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::engine_display)
{
    ui->setupUi(this);
}

engine_display::~engine_display()
{
    delete ui;
}
