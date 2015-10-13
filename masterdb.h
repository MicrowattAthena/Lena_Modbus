extern "C" {
#ifndef masterDB_H
#define masterDB_H

#include "EC/EC_registers.h"
#include <stdint.h>

// Char identifiers used for DB

#define ENVIRONMENTAL_CONTROL 'e'
#define LCD_CONTROL 'l'
#define GENERAL_BOARD 'g'
#define BEDROOM 'b'
#define SALOON 's'
#define REGISTERS 'r'
#define COILS 'c'
#define ENGINE 'E'
#define DCSYS 'D'
#define ACSYS 'A'
#define HVAC 'H'
#define TANKS 'T'
#define RR 'R'
#define GPS 'G'
#define SONAR 'S'
#define LIGHTS 'L'
#define LCD 'C'
#define GYRO 'Y'
#define ALARM 'M'
#define WARNING 'W'
#define GENERAL_ENGINE '1'


int initialiseDB();
int resetflags();
int managelcd();
int senddatatoGUI(char,char,char, int);
int getdatafromGUI(char,char,char, int, uint16_t);
int createqueue(char,char,char,int,int);
int writeDB(char, char, char);
int pollslaves();
int setslaveRTU(void);
int compareDB(char, char, char);
 int writequeue(char,char,char,int, int);
 void getqueuedata(char, char, char, int, int);
 void processqueue();
 void deletequeuedata();
#endif // masterDB_H
}
