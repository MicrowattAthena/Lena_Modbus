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

       //on a continousloop
            //poll slaves
            //update LCDs
            //set alarm states for LCD??
            //update display

       while(1){
        pollslaves();
        managelcd();
        senddatatoGUI();
        }
    }

    return a.exec();
}
