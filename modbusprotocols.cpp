#include "modbusprotocols.h"
#include <stdio.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus.h>

#define DEBUG_ENABLED
#define TIMEOUTDURATION 2.0


extern "C" {

modbus_t *ctx;
uint16_t register_buffer[64];
uint8_t coil_buffer[64];
int errno;

int initialiseRTU(void){
ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'E',8,1);
if (ctx == NULL) {
#ifdef DEBUG_ENABLED
    printf("Could not initialise modbus\n");
#endif
    return 0;
}
else {
#ifdef DEBUG_ENABLED
    printf("Modbus initialised\n");
#endif
    return 1;
    }
}


int setRTUmode(void){
int success;
 modbus_set_debug(ctx,TRUE);

success = modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS232);
if (success == 0) {
#ifdef DEBUG_ENABLED
    printf("RTU Set Successfully\n");
#endif
    return 1;
}else {
#ifdef DEBUG_ENABLED
 fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
#endif

    return 0;
    }
}

int settimeouts(void){

    //Causes Memory Access Violation?? Not sure on cause yet
  //modbus_set_byte_timeout(ctx,TIMEOUTDURATION,0);
   //modbus_set_response_timeout(ctx,TIMEOUTDURATION,0);
return 1;
}


int RTU_connect(void){
if (modbus_connect(ctx)==0){
    return 1;
}else{
#ifdef DEBUG_ENABLED
    printf("Failed to Connect");
    modbus_free(ctx);
#endif
return 0;
    }
}


int readaddresses(int initialaddress,int numberofregisters){

    int rc;


    rc = modbus_read_registers(ctx, initialaddress, numberofregisters, register_buffer);
    if (rc == -1) {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return 0;
        }else{
       return 1;
    }
}

int readcoils(int initialaddress, int numberofcoils){

    int rc;


    rc = modbus_read_bits(ctx,initialaddress,numberofcoils, coil_buffer);
    if (rc== -1){
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return 0;
    }else{

        return 1;
    }

}

int setmodbusslave(int id){
    modbus_set_slave(ctx,id);
    return 1;
}


int report_slave_ID(){
    uint8_t slaveresponse_bytes[MODBUS_MAX_PDU_LENGTH];
    int rc;

    rc = modbus_report_slave_id(ctx, MODBUS_MAX_PDU_LENGTH, slaveresponse_bytes);
    if (rc > 1) {
        printf("Run Status Indicator: %s\n", slaveresponse_bytes[1] ? "ON" : "OFF");
    }
    return 1;
}
}

