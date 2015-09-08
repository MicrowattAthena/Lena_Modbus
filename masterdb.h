extern "C" {
#ifndef masterDB_H
#define masterDB_H

#include "EC/EC_registers.h"

// Char identifiers used for DB

#define ENVIRONMENTAL_CONTROL 'e'
#define LCD_CONTROL 'l'
#define GENERAL_BOARD 'g'
#define BEDROOM 'b'
#define SALOON 's'
#define REGISTERS 'r'
#define COILS 'c'

int initialiseDB();
int writeDB(char, char, char);

#endif // masterDB_H
}
