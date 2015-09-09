extern "C" {
#ifndef MODBUSMANAGEMENT_H
#define MODBUSMANAGEMENT_H

int initialisemodbus(void);
int testread(void);
int readLCDslave(int, char);
int readgeneralslave(int, char);
int readECslave(int, char);
int writeLCDtime(int);
#endif // MODBUSMANAGEMENT_H

}
