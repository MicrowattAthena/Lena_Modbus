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



     qWarning() << "Initialised Worker Thread";
     //Initialise Modbus

   if (initialisemodbus()){
    qWarning() << "WT:Setting RTUs";

    setslaveRTU();
   initialiseLCDlinks();
        while(1){

         qWarning() << "WT:Polling Slaves";
         processqueue();
         pollslaves();
         processqueue();
         managelcd();
         processqueue();

         }

     }else{
        qWarning() << "Modbus Initialisation Failed";

        //Sent signal for failed modbus!
    }
}

