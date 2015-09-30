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


         setslaveRTU();

        while(1){
         pollslaves();
         managelcd();

         }
     }
}
