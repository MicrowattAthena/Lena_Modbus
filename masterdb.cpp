#include "masterdb.h"
#include "modbusmanagement.h"

extern "C" {

//0 is the terminating character - illegal modbus data address.
const int LCDSlaveIDs[] = { 1,0};
const int GeneralSlaveIDs[] = { 0 };
const int ECSlaveIDs[] = { 0 };


int initialiseDB () {
//if DB doesn't exist then create


    // check slave ids and types of slave
    for (int i = 0; LCDSlaveIDs[i] != 0;i++)
        //pass ID to modbusmanagement
        readLCDslave(LCDSlaveIDs[i]);

    for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
        readgeneralslave(GeneralSlaveIDs[i]);

    for (int i = 0; ECSlaveIDs[i] != 0; i++)
        readECslave(ECSlaveIDs[i]);


    return 0;
}

}
