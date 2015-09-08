extern "C" {
#ifndef MODBUSPROTOCOLS_H
#define MODBUSPROTOCOLS_H

#include <stdint.h>

extern uint16_t register_buffer[64];
extern uint8_t coil_buffer[64];

int initialiseRTU(void);
int setRTUmode(void);
int settimeouts(void);
int RTU_connect(void);
int report_slave_ID(void);
int readaddresses(int, int);
int setmodbusslave(int);
int readcoils(int, int);
int testfunction(void);

#endif // MODBUSPROTOCOLS_H
}
