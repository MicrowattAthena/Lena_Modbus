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

    initialisemodbus();
    testread();
    return a.exec();
}
