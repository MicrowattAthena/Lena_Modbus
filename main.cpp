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
        //set RTC for slaves
        initialiseDB();
    }
        //on a continousloop
             //poll slaves
             //process update queue
             //update display

        //interrupt when user makes change on display

    return a.exec();
}
