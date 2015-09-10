#include "widget.h"
#include "modbusmanagement.h"
#include "masterdb.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    // Create and Show Widget
    QApplication a(argc, argv);
    Widget w;
    w.show();



    //Initialise Modbus

   if (initialisemodbus()==1){


 //poll slaves
       //Checks slave device values against DB. If a value is different to the DB, and the DB has not been changed
       //on this cycle, change DB value.
            //update LCDs
            //set alarm states for LCD??
            //update GUI


       while(1){
        pollslaves();
        managelcd();
        senddatatoGUI();

        }
    }

    return a.exec();
}
