#include "modbusprotocols.h"
#include <stdio.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus.h>
#include <time.h>
#include <QDebug>
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
    qWarning() << "Modbus failed to initialise";
#endif
    return 0;
}
else {
#ifdef DEBUG_ENABLED
    qWarning() << "Modbus Initialised";

#endif
    return 1;
    }
}
int setdebugmode(){
    modbus_set_debug(ctx, TRUE);
}

int setRTUmode(void){
int success;

success = modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS485);
if (success == 0) {
#ifdef DEBUG_ENABLED
  qWarning() << "RTU set succesfully";
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

  modbus_set_byte_timeout(ctx,TIMEOUTDURATION,0);
  modbus_set_response_timeout(ctx,TIMEOUTDURATION,0);
return 1;
}


int RTU_connect(void){
  modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_PROTOCOL);
if (modbus_connect(ctx)==0){
    return 1;
}else{
#ifdef DEBUG_ENABLED
    qWarning() << "Failed to Connect";
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
     //     qWarning() << register_buffer[1];
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
   qWarning() << "Slave ID:";
    qWarning() << id;

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

int write_registers(int address, int length, uint16_t data[]){
int retries = 4;

do {
    if (modbus_write_registers(ctx,address,length,data)==length){
        qWarning() << "Successful Write";
        return 1;
    }else{
        retries--;
        qWarning() << "Failed to Write, re-attempting";
        qWarning() << address;
        qWarning() << length;
    }
}
while( retries >  0);
     qWarning() << "Failed to Write, reached retry limit!";
      return 0;
}

int write_coils(int address, int length, uint8_t data[]){
    int retries = 3;

    do {
        if (modbus_write_bits(ctx,address,length,data)==length){
            qWarning() << "Successful Write";
            return 1;
        }else{
            retries--;
            qWarning() << "Failed to Write, re-attempting";
        }
    }
    while( retries >=  0);
         qWarning() << "Failed to Write, reached retry limit!";
          return 0;
}

int write_single_register(int address, uint16_t data){
    int retries = 3;
    do {
        if (modbus_write_register(ctx,address,data)==1){
            qWarning() << "Successful Write";
            return 1;
        }else{
            retries--;
            qWarning() << "Failed to Write, re-attempting";
        }
    }
    while( retries >=  0);
         qWarning() << "Failed to Write, reached retry limit!";
          return 0;
}

int write_single_coil(int address, uint8_t data){
    int retries = 3;

    do {
        if (modbus_write_bit(ctx,address,data)==1){
            qWarning() << "Successful Write";
            return 1;
        }else{
            retries--;
            qWarning() << "Failed to Write, re-attempting";
        }
    }
    while( retries <=  0);
         qWarning() << "Failed to Write, reached retry limit!";
          return 0;
}
}

