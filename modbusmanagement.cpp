#include <modbusmanagement.h>
#include <stdlib.h>
#include <modbusprotocols.h>
extern "C" {

//Sets up and Connects Modbus
int initialisemodbus(void){

    initialiseRTU();
    setRTUmode();
    settimeouts();
    RTU_connect();


    return 0;

}

//Reads Data from all slaves and stores internally

int testread(void){
    setmodbusslave(1);
    readaddresses();
    }

}
