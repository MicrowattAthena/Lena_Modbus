#include <modbusmanagement.h>
#include <stdlib.h>
#include <modbusprotocols.h>
extern "C" {

//Sets up and Connects Modbus
int initialisemodbus(void){

    initialiseRTU();
    setRTUmode();
    settimeouts();
    if (RTU_connect()==0){
        return 0;
    }else{
        return -1;
    }

}

//Reads Data from all slaves and stores internally

int testread(void){
    setmodbusslave(1);
    readaddresses();
    }

}
