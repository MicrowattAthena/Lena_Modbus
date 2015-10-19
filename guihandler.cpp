#include "guihandler.h"
#include "ec_saloon.h"
#include "EC/EC_registers.h"
#include <QObject>
#include <QTimer>
#include <QDebug>

extern guihandler *handler;

guihandler::guihandler()
{

}

void guihandler::initialise(){

    QTimer *timer = new QTimer();
    timer->setInterval(20000);
    QObject::connect(
                timer, SIGNAL(timeout()),
                handler, SLOT(updateGUI()));
    timer->start();
}

void guihandler::updateGUI(){
       qWarning() << "Updating GUI";
   //Connect this signal to slots for updating on each screen
    emit this->requestupdate();
}


