#include "guihandler.h"
#include "ec_saloon.h"
#include <QObject>
#include <QTimer>
guihandler::guihandler()
{

}

void guihandler::initialise(){
    QTimer *timer = new QTimer();
    timer->setInterval(5000);
    QObject::connect(
                timer, SIGNAL(timeout()),
                this, SLOT(updateGUI()));
    timer->start();

    // Create connection from signals to slots
    EC_Saloon *ecshandler = new EC_Saloon();
    QObject::connect(
                this, SIGNAL(requestupdate()),
                ecshandler,SLOT(update_ecs_values()));

}
void guihandler::updateGUI(){

   //Connect this signal to slots for updating on each screen
    emit this->requestupdate();
}
