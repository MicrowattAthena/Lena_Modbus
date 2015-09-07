#include "modbusprotocols.h"
#include <modbus/modbus-rtu.h>
#include <modbus/modbus.h>
#include <stdio.h>

#define DEBUG_ENABLED
#define TIMEOUTDURATION 2.0


extern "C" {
modbus_t *ctx;

int errno;

int initialiseRTU(void){
ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'E',8,1);
if (ctx == NULL) {
#ifdef DEBUG_ENABLED
    printf("Could not initialise modbus\n");
#endif
    return -1;
}
else {
#ifdef DEBUG_ENABLED
    printf("Modbus initialised\n");
#endif
    return 0;
    }
}


int setRTUmode(void){
int success; int serialmode;
 modbus_set_debug(ctx,TRUE);

success = modbus_rtu_set_serial_mode(ctx, MODBUS_RTU_RS232);
if (success == 0) {
#ifdef DEBUG_ENABLED
    printf("RTU Set Successfully\n");
#endif
    return 0;
}
else {
#ifdef DEBUG_ENABLED
 fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
#endif
    return -1;
    }
}

int settimeouts(void){
    modbus_set_byte_timeout(ctx,  TIMEOUTDURATION,0);
  modbus_set_response_timeout(ctx,TIMEOUTDURATION,0);
return 0;
}


int RTU_connect(void){
if (modbus_connect(ctx)==0){
    return 0;
}else{
#ifdef DEBUG_ENABLED
    printf("Failed to Connect");
    modbus_free(ctx);
#endif
return -1;
    }
}


int readaddresses(){

    uint16_t tab_reg[64];
    int rc;
    int i;

    rc = modbus_read_registers(ctx, 256, 10, tab_reg);
    if (rc == -1) {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
        }else{
        for (i=0; i < rc; i++) {
            printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
            }
        }
    return 0;
}


int setmodbusslave(int id){
    modbus_set_slave(ctx,id);
    return 0;
}


int report_slave_ID(){
    uint8_t slaveresponse_bytes[MODBUS_MAX_PDU_LENGTH];
    int rc;

    rc = modbus_report_slave_id(ctx, MODBUS_MAX_PDU_LENGTH, slaveresponse_bytes);
    if (rc > 1) {
        printf("Run Status Indicator: %s\n", slaveresponse_bytes[1] ? "ON" : "OFF");
    }
}
}

