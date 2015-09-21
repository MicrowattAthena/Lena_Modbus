#include "workerthread.h"
#include "modbusmanagement.h"
#include "masterdb.h"
#include "QtCore"
#include "QDebug"
workerthread::workerthread()
{

}

void workerthread::run()
{

     qDebug() << "Running";
     //Initialise Modbus

    if (initialisemodbus()){


  //poll slaves
        //Checks slave device values against DB. If a value is different to the DB, and the DB has not been changed
        //on this cycle, change DB value.
             //update LCDs
             //set alarm states for LCD??
             //update GUI
         setslaveRTU();

        while(1){
         pollslaves();
         managelcd();
         senddatatoGUI();

         }
     }
}
