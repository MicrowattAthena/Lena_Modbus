extern "C" {
#ifndef MODBUSMANAGEMENT_H
#define MODBUSMANAGEMENT_H

int initialisemodbus(void);
int testread(void);
int readLCDslave(int);
int readgeneralslave(int);
int readECslave(int);
#endif // MODBUSMANAGEMENT_H

}
