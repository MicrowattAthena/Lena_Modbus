#include "widget.h"
#include "modbusmanagement.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    // Create and Show Widget
    QApplication a(argc, argv);
    Widget w;
    w.show();


    //Initialise Modbus

    if (initialisemodbus()==0){
     testread();
    }

    return a.exec();
}
