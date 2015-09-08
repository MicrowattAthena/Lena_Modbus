#include "masterdb.h"
#include "modbusmanagement.h"
#include "modbusprotocols.h"
#include "EC/EC_registers.h"
extern "C" {

//0 is the terminating character - illegal modbus data address.
// "S" -identifier - Located in Saloon
// "B" -identifier - Located in Bedroom

    const int LCDSlaveIDs[] = { 1,0};
    const char LCDSlaveName[] = { SALOON, '0'};

    const int GeneralSlaveIDs[] = { 0 };
    const char GeneralSlaveName[] = {'0'};

    const int ECSlaveIDs[] = {2 ,3, 0 };
    const char ECSlaveName[] = { SALOON, BEDROOM, '0'};

struct database {
   int EC_Bedroom_Registers[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Saloon_Registers[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Bedroom_Coils[COIL_ENVC_MAX - COILS_ENVC_BASE];
   int EC_Saloon_Coils[COIL_ENVC_MAX - COILS_ENVC_BASE];
};

struct database MasterDB;

int initialiseDB () {
//create master Database

    // check slave ids and types of slave
    for (int i = 0; LCDSlaveIDs[i] != 0;i++)
        //pass ID to modbusmanagement
        readLCDslave(LCDSlaveIDs[i],LCDSlaveName[i]);

    for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
        readgeneralslave(GeneralSlaveIDs[i],GeneralSlaveName[i]);

    for (int i = 0; ECSlaveIDs[i] != 0; i++)
        readECslave(ECSlaveIDs[i],ECSlaveName[i]);


    return 0;
}


int writeDB(char slavetype, char slavename, char addresstype){

    int i;
// Switch Case Slavetype (EC, General, LCD)
    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:
        switch (slavename) {
        case BEDROOM:
            switch (addresstype) {
            case REGISTERS:
                //write to EC Bedroom registers
                for (i = 0; i <= (REG_ENVC_MAX - REGS_ENVC_BASE); i++)
                   MasterDB.EC_Bedroom_Registers[i] = register_buffer[i];
                break;
            case COILS:
                //Write to EC Bedroom Coils
                for (i = 0; i <= (COIL_ENVC_MAX - COILS_ENVC_BASE); i++)
                    MasterDB.EC_Bedroom_Coils[i] = coil_buffer[i];
                break;
            default:
                //SHOULDNT HAPPEN
                break;
            }
            break;
        case SALOON:
            switch (addresstype) {
            case REGISTERS:
                //Write to EC Saloon Registers
                for (i = 0; i <= (REG_ENVC_MAX - REGS_ENVC_BASE); i++)
                    MasterDB.EC_Saloon_Registers[i] = register_buffer[i];
                break;
            case COILS:
                //Write to EC Saloon Coils
                for (i=0; i <= (COIL_ENVC_MAX - COILS_ENVC_BASE); i++)
                    MasterDB.EC_Saloon_Coils[i] = coil_buffer[i];
            break;
            default:
                //SHOULDNT HAPPEN
                break;
            }
            break;
        default:
            //SHOULDNT HAPPEN
            break;
        }
        break;
    case GENERAL_BOARD:
        //code
        break;
    case LCD_CONTROL:
        //code
        break;
    default:
        //SHOULDNT HAPPEN
        break;
    }

    return 0;
}
}
