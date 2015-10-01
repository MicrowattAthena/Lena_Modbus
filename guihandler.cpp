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
    timer->setInterval(5000);
    QObject::connect(
                timer, SIGNAL(timeout()),
                handler, SLOT(updateGUI()));
    timer->start();

    // Create connection from signals to slots
    //EC_Saloon *ecshandler = new EC_Saloon();
// QObject::connect(this, &guihandler::requestupdate, ecshandler,&EC_Saloon ::update_ecs_values);

}
void guihandler::updateGUI(){
       qWarning() << "Updating GUI";
   //Connect this signal to slots for updating on each screen
    emit this->requestupdate();
}


