#include "masterdb.h"
#include "modbusmanagement.h"
#include "modbusprotocols.h"
#include "EC/EC_registers.h"
#include "workerthread.h"
#include "LCD/lcd_registers.h"
#include "General/general_registers.h"
#include <QDebug>
extern "C" {

//0 is the terminating character - illegal modbus data address.

    const int LCDSlaveIDs[] = { 1,2, 0 };
    const char LCDSlaveName[] = { SALOON, BEDROOM, '0' };

  //  const int GeneralSlaveIDs[] = { 5, 0 };
  //  const char GeneralSlaveName[] = {GENERAL_ENGINE, '0'};

    const int GeneralSlaveIDs[] = {0};
    const char GeneralSlaveName[] = {'0'};

    const int ECSlaveIDs[] = {3,4,0 };
   const char ECSlaveName[] = { SALOON, BEDROOM, '0'};

  //  const int ECSlaveIDs[] = { 0 };
  //  const char ECSlaveName[] = {'0'};

struct database {

   int EC_Bedroom_Registers[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Saloon_Registers[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Bedroom_Coils[COIL_ENVC_MAX - COILS_ENVC_BASE];
   int EC_Saloon_Coils[COIL_ENVC_MAX - COILS_ENVC_BASE];

   int LCD_Saloon_Engine[REG_ENG_MAX - ENGINE_BASE];
   int LCD_Saloon_DCsys[REG_DCSYS_MAX - DCSYSTEM_BASE];
   int LCD_Saloon_ACsys[REG_ACSYS_MAX - ACSYSTEM_BASE];
   int LCD_Saloon_HVAC[REG_HVAC_MAX - HVAC_BASE];
   int LCD_Saloon_Tanks[REG_TANKS_MAX - TANKS_BASE];
   int LCD_Saloon_RR[REG_RR_MAX - RR_BASE];
   int LCD_Saloon_GPS[REG_GPS_MAX - GPS_BASE];
   int LCD_Saloon_Sonar[REG_SONAR_MAX - SONAR_BASE];
   int LCD_Saloon_Lights[REG_LIGHTS_MAX - LIGHTS_BASE];
   int LCD_Saloon_LCD[REG_LCD_MAX - LCD_BASE];
   int LCD_Saloon_Gyro[REG_GYRO_MAX - GYRO_BASE];
   int LCD_Saloon_Alarm[COIL_ALRM_MAX - ALARMS_BASE];
   int LCD_Saloon_Warning[COIL_WARN_MAX - WARNINGS_BASE];

  /* int LCD_Bedroom_Engine[REG_ENG_MAX - ENGINE_BASE];
   int LCD_Bedroom_DCsys[REG_DCSYS_MAX - DCSYSTEM_BASE];
   int LCD_Bedroom_ACsys[REG_ACSYS_MAX - ACSYSTEM_BASE];
   int LCD_Bedroom_HVAC[REG_HVAC_MAX - HVAC_BASE];
   int LCD_Bedroom_Tanks[REG_TANKS_MAX - TANKS_BASE];
   int LCD_Bedroom_RR[REG_RR_MAX - RR_BASE];
   int LCD_Bedroom_GPS[REG_GPS_MAX - GPS_BASE];
   int LCD_Bedroom_Sonar[REG_SONAR_MAX - SONAR_BASE];
   int LCD_Bedroom_Lights[REG_LIGHTS_MAX - LIGHTS_BASE];
   int LCD_Bedroom_LCD[REG_LCD_MAX - LCD_BASE];
   int LCD_Bedroom_Gyro[REG_GYRO_MAX - GYRO_BASE];
   int LCD_Bedroom_Alarm[COIL_ALRM_MAX - ALARMS_BASE];
   int LCD_Bedroom_Warning[COIL_WARN_MAX - WARNINGS_BASE]; */

   int General_Engine_Registers[REG_GENERAL_MAX - REG_ANALOG_IN12];
   int General_Engine_Coils[COIL_GENERAL_MAX - COILS_GENERAL_BASE];

   int EC_Bedroom_Registers_Flag[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Saloon_Registers_Flag[REG_ENVC_MAX - REGS_ENVC_BASE];
   int EC_Bedroom_Coils_Flag[COIL_ENVC_MAX - COILS_ENVC_BASE];
   int EC_Saloon_Coils_Flag[COIL_ENVC_MAX - COILS_ENVC_BASE];

   int LCD_Saloon_Engine_Flag[REG_ENG_MAX - ENGINE_BASE];
   int LCD_Saloon_DCsys_Flag[REG_DCSYS_MAX - DCSYSTEM_BASE];
   int LCD_Saloon_ACsys_Flag[REG_ACSYS_MAX - ACSYSTEM_BASE];
   int LCD_Saloon_HVAC_Flag[REG_HVAC_MAX - HVAC_BASE];
   int LCD_Saloon_Tanks_Flag[REG_TANKS_MAX - TANKS_BASE];
   int LCD_Saloon_RR_Flag[REG_RR_MAX - RR_BASE];
   int LCD_Saloon_GPS_Flag[REG_GPS_MAX - GPS_BASE];
   int LCD_Saloon_Sonar_Flag[REG_SONAR_MAX - SONAR_BASE];
   int LCD_Saloon_Lights_Flag[REG_LIGHTS_MAX - LIGHTS_BASE];
   int LCD_Saloon_LCD_Flag[REG_LCD_MAX - LCD_BASE];
   int LCD_Saloon_Gyro_Flag[REG_GYRO_MAX - GYRO_BASE];
   int LCD_Saloon_Alarm_Flag[COIL_ALRM_MAX - ALARMS_BASE];
   int LCD_Saloon_Warning_Flag[COIL_WARN_MAX - WARNINGS_BASE];

  /* int LCD_Bedroom_Engine[REG_ENG_MAX - ENGINE_BASE];
   int LCD_Bedroom_DCsys[REG_DCSYS_MAX - DCSYSTEM_BASE];
   int LCD_Bedroom_ACsys[REG_ACSYS_MAX - ACSYSTEM_BASE];
   int LCD_Bedroom_HVAC[REG_HVAC_MAX - HVAC_BASE];
   int LCD_Bedroom_Tanks[REG_TANKS_MAX - TANKS_BASE];
   int LCD_Bedroom_RR[REG_RR_MAX - RR_BASE];
   int LCD_Bedroom_GPS[REG_GPS_MAX - GPS_BASE];
   int LCD_Bedroom_Sonar[REG_SONAR_MAX - SONAR_BASE];
   int LCD_Bedroom_Lights[REG_LIGHTS_MAX - LIGHTS_BASE];
   int LCD_Bedroom_LCD[REG_LCD_MAX - LCD_BASE];
   int LCD_Bedroom_Gyro[REG_GYRO_MAX - GYRO_BASE];
   int LCD_Bedroom_Alarm[COIL_ALRM_MAX - ALARMS_BASE];
   int LCD_Bedroom_Warning[COIL_WARN_MAX - WARNINGS_BASE]; */

   int General_Engine_Registers_Flag[REG_GENERAL_MAX - REG_ANALOG_IN12];
   int General_Engine_Coils_Flag[COIL_GENERAL_MAX - COILS_GENERAL_BASE];
};

struct queuefile {
    char slavetype;
    char slavename;
    char addresstype;
    int address;
    int value;
};
   queuefile GUIqueuefile[30];
   int queuecounter = 0;

struct database MasterDB;
int setslaveRTU(void){

    for (int i = 0; LCDSlaveIDs[i] != 0;i++)
         //pass ID to modbusmanagement
         //Set RTC for each LCD Slave
         writeLCDRTU(LCDSlaveIDs[i]);

     for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
         writegeneralRTU(GeneralSlaveIDs[i]);

     return 1;
}

int resetflags() {
    int i;
    for (i=REGS_ENVC_BASE; i <= REG_ENVC_MAX; i++){
        MasterDB.EC_Bedroom_Registers_Flag[i - REGS_ENVC_BASE]= 0;
        MasterDB.EC_Saloon_Registers_Flag[i - REGS_ENVC_BASE] = 0;
    }
    for (i= REG_ANALOG_IN12; i<= REG_GENERAL_MAX; i++)
        MasterDB.General_Engine_Registers_Flag[i - REG_ANALOG_IN12]=0;
    for (i= COILS_GENERAL_BASE; i <= COIL_GENERAL_MAX; i++)
        MasterDB.General_Engine_Coils_Flag[i - COILS_GENERAL_BASE]=0;

    for (i= ENGINE_BASE; i<= REG_ENG_MAX; i++)
        MasterDB.LCD_Saloon_Engine_Flag[i - ENGINE_BASE]=0;
    for (i = DCSYSTEM_BASE; i<= REG_DCSYS_MAX; i++)
        MasterDB.LCD_Saloon_DCsys_Flag[i - DCSYSTEM_BASE]=0;
    for (i= ACSYSTEM_BASE; i<= REG_ACSYS_MAX; i++)
        MasterDB.LCD_Saloon_ACsys_Flag[i - ACSYSTEM_BASE]=0;
    for (i=HVAC_BASE; i<= REG_HVAC_MAX; i++)
        MasterDB.LCD_Saloon_HVAC_Flag[i - HVAC_BASE]=0;
    for (i=TANKS_BASE; i<= REG_TANKS_MAX; i++)
        MasterDB.LCD_Saloon_Tanks_Flag[i - TANKS_BASE]=0;
    for (i= RR_BASE; i<= REG_RR_MAX; i++)
        MasterDB.LCD_Saloon_RR_Flag[i - RR_BASE]=0;
    for (i=GPS_BASE; i <= REG_GPS_MAX; i++)
        MasterDB.LCD_Saloon_GPS_Flag[i - GPS_BASE]=0;
    for (i=SONAR_BASE; i<= REG_SONAR_MAX; i++)
        MasterDB.LCD_Saloon_Sonar_Flag[i - SONAR_BASE]= 0;
    for (i=LIGHTS_BASE; i<= REG_LIGHTS_MAX; i++)
        MasterDB.LCD_Saloon_Lights_Flag[i - LIGHTS_BASE]=0;
    for (i=LCD_BASE; i<= REG_LCD_MAX; i++ )
        MasterDB.LCD_Saloon_LCD_Flag[i - LCD_BASE]=0;
    for (i=GYRO_BASE; i<= REG_GYRO_MAX; i++)
        MasterDB.LCD_Saloon_Gyro_Flag[i - GYRO_BASE]= 0;
    for (i=ALARMS_BASE; i<=COIL_ALRM_MAX; i++)
        MasterDB.LCD_Saloon_Alarm_Flag[i - ALARMS_BASE] = 0;
    for (i=WARNINGS_BASE; i<=COIL_WARN_MAX; i++)
        MasterDB.LCD_Saloon_Warning_Flag[i - WARNINGS_BASE]=0;
    return 1;
}

int pollslaves() {
    // Set Flags to 0
    resetflags();

    // check slave ids and types of slave
     processqueue();
  qWarning() << "Reading LCDs";
   for (int i = 0; LCDSlaveIDs[i] != 0;i++)
        //pass ID to modbusmanagement
        readLCDslave(LCDSlaveIDs[i],LCDSlaveName[i]);
    processqueue();
  qWarning() << "Reading Generals";
    for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
        readgeneralslave(GeneralSlaveIDs[i],GeneralSlaveName[i]);
     processqueue();
  qWarning() << "Reading ECs";
    for (int i = 0; ECSlaveIDs[i] != 0; i++)
        readECslave(ECSlaveIDs[i],ECSlaveName[i]);


    return 1;
}


int managelcd() {
    //Most of the LCD Data is obtained from other slave devices.
    //The program needs to set the correct values to the LCD DB and then rewrite to the LCDs.

    buildlcdDB();

    //Alarms also need to be monitored. Check Alarm States and set alarm if necessary
    return 1;
}

int buildlcdDB() {
//Not so simple function: some data is shared between slaves. However, determining what data to use if the value is changed
// in one slave isnt so simple. If a flag has been set for the masterDB, indicating that the value has changed outside of
// the program, then that value should not be overwritten.
// A messy solution, but should work.

    // EC to LCD

    if (MasterDB.LCD_Saloon_HVAC_Flag[(REG_HVAC_MAX - REG_HVAC_MSBEDSETTEMP)]){
         MasterDB.EC_Bedroom_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)] = MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_MSBEDTEMP)];
    }else{
         MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_MSBEDTEMP)] = MasterDB.EC_Bedroom_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)];
    }

    if (MasterDB.LCD_Saloon_HVAC_Flag[(REG_HVAC_MAX - REG_HVAC_MSBEDHUMID)]){
         MasterDB.EC_Bedroom_Registers[(REG_ENVC_MAX - REG_HUMIDITY)] = MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_MSBEDHUMID)];
    }else{
         MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_MSBEDHUMID)] = MasterDB.EC_Bedroom_Registers[(REG_ENVC_MAX - REG_HUMIDITY)];
    }

    if (MasterDB.LCD_Saloon_HVAC_Flag[(REG_HVAC_MAX - REG_HVAC_SALNTEMP)]){
        MasterDB.EC_Saloon_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)] = MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_SALNTEMP)];
    }else{
        MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_SALNTEMP)] = MasterDB.EC_Saloon_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)];
    }

    if (MasterDB.LCD_Saloon_HVAC_Flag[(REG_HVAC_MAX - REG_HVAC_SALNHUMID)]){
 MasterDB.EC_Saloon_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)] = MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_SALNHUMID)];
    }else{
   MasterDB.LCD_Saloon_HVAC[(REG_HVAC_MAX - REG_HVAC_SALNHUMID)] = MasterDB.EC_Saloon_Registers[(REG_ENVC_MAX - REG_TEMPR_ROOM)];
    }



    return 1;
}

void getqueuedata(char slavetype, char slavename, char addresstype, int address, int value)
{
    uint newdata = 1; uint i;
    queuefile tempqueue;
    tempqueue.slavetype = slavetype;
    tempqueue.slavename = slavename;
    tempqueue.addresstype = addresstype;
    tempqueue.address = address;
    tempqueue.value = value;


 for (i = 0; i<= queuecounter; i++)
 {

    if ( (tempqueue.address == GUIqueuefile[i].address) && (tempqueue.slavename == GUIqueuefile[i].slavename) &&
         (tempqueue.addresstype == GUIqueuefile[i].addresstype) && (tempqueue.slavetype == GUIqueuefile[i].slavetype))
    {
        qWarning() << "Updating Value in Queue";
     GUIqueuefile[i].value = tempqueue.value;
     newdata = 0;
    }

 }

    if (newdata == 1)
    {
        qWarning() << "Adding Value to Queue";
        GUIqueuefile[queuecounter].slavetype = slavetype;
         GUIqueuefile[queuecounter].slavename = slavename;
          GUIqueuefile[queuecounter].addresstype = addresstype;
           GUIqueuefile[queuecounter].address = address;
            GUIqueuefile[queuecounter].value = value;
        queuecounter +=1;
    }

}

void deletequeuedata () {
    qWarning()<< "Deleting Queue";
    queuecounter = 0;
}

void processqueue(){
    qWarning()<< "Processing Queue";
    uint i;
    for (i = queuecounter;i <= 0; i--)
    {
    writequeue(GUIqueuefile[i].slavetype, GUIqueuefile[i].slavename, GUIqueuefile[i].addresstype, GUIqueuefile[i].address,GUIqueuefile[i].value);
    }
    deletequeuedata();
}

int writequeue(char slavetype, char slavename, char addresstype, int address, int value) {

    //This needs to be written to slaves

    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:


        switch (slavename) {
        case BEDROOM:
            setmodbusslave(4);
            switch (addresstype) {
            case REGISTERS:
                 write_single_register(address - 1,value);
                 return 1;
            case COILS:
                 write_single_coil(address - 1,value);
                 return 1;
            break;
            }

         case SALOON:
             setmodbusslave(3);
            switch (addresstype) {
            case REGISTERS:
                write_single_register(address - 1,value);
                return 1;
            case COILS:
                write_single_coil(address - 1,value);
                return 1;
            break;
            }
        }

    case GENERAL_BOARD:

        switch (slavename){
        case GENERAL_ENGINE:
            setmodbusslave(0);
            switch (addresstype) {
            case REGISTERS:
                write_single_register(address - 1,value);
                return 1;
            case COILS:
                write_single_coil(address - 1,value);
                return 1;
            break;
        }


    break;
    }




    case LCD_CONTROL:
    setmodbusslave(1);
            switch (addresstype) {
            case ALARM:
                write_single_coil(address - 1,value);
                break;
            case WARNING:
                write_single_coil(address - 1, value);
                break;
            default:
                write_single_register(address - 1,value);
                break;
            break;
            }

    setmodbusslave(2);
     switch (addresstype) {
    case ALARM:
        write_single_coil(address - 1,value);
        break;
    case WARNING:
        write_single_coil(address - 1, value);
        break;
    default:
        write_single_register(address - 1,value);
        break;
    break;
    }

}
return 0;
}

int senddatatoGUI(char slavetype, char slavename, char addresstype, int address) {
    // The GUI will display some information from the DB.
    
    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:

        switch (slavename) {
        case BEDROOM:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.EC_Bedroom_Registers[address -1];
            case COILS:
                return MasterDB.EC_Bedroom_Coils[address - 1];
            break;
            }

         case SALOON:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.EC_Saloon_Registers[address - 1];
            case COILS:
                return MasterDB.EC_Saloon_Coils[address - 1];
            break;
            }
        }

    case GENERAL_BOARD:

        switch (slavename){
        case GENERAL_ENGINE:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.General_Engine_Registers[address - 1];
            case COILS:
                return MasterDB.General_Engine_Coils[address - 1];
            break;
        }


    break;
    }




    case LCD_CONTROL:

            switch (addresstype) {
            case ENGINE:
                return MasterDB.LCD_Saloon_Engine[address - 1];
            case DCSYS:
                return MasterDB.LCD_Saloon_DCsys[address - 1];
            case ACSYS:
                return MasterDB.LCD_Saloon_ACsys[address - 1];
            case HVAC:
                return MasterDB.LCD_Saloon_HVAC[address - 1];
            case TANKS:
                return MasterDB.LCD_Saloon_Tanks[address -1];
            case RR:
                return MasterDB.LCD_Saloon_RR[address - 1];
            case GPS:
                return MasterDB.LCD_Saloon_GPS[address - 1];
            case SONAR:
                return MasterDB.LCD_Saloon_Sonar[address - 1];
            case LIGHTS:
                return MasterDB.LCD_Saloon_Lights[address - 1];
            case LCD:
                return MasterDB.LCD_Saloon_LCD[address - 1];
            case GYRO:
                return MasterDB.LCD_Saloon_Gyro[address - 1];
            break;
            }


}
return 0;
}


int writeDB(char slavetype, char slavename, char addresstype){

    int i;
// Switch Case Slavetype (EC, General, LCD)
// Switch Case Slave Identifier (Location)
// Switch Case Register Type
// Writes Register and Coil Buffers to Master Database if value has not changed before
    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:
        switch (slavename) {
        case BEDROOM:
            switch (addresstype) {
            case REGISTERS:
                //write to EC Bedroom registers
                for (i = 0; i <= (REG_ENVC_MAX - REGS_ENVC_BASE); i++)
                    if ((MasterDB.EC_Bedroom_Registers_Flag[i] == 0)&& (MasterDB.EC_Bedroom_Registers[i] != register_buffer[i])){
                        MasterDB.EC_Bedroom_Registers[i] = register_buffer[i];
                        MasterDB.EC_Bedroom_Registers_Flag[i] = 1;
                    }


                break;
            case COILS:
                //Write to EC Bedroom Coils
                for (i = 0; i <= (COIL_ENVC_MAX - COILS_ENVC_BASE); i++)
                   if ((MasterDB.EC_Bedroom_Coils_Flag[i] == 0)&& (MasterDB.EC_Bedroom_Coils[i] != coil_buffer[i])){
                        MasterDB.EC_Bedroom_Coils[i] = coil_buffer[i];
                        MasterDB.EC_Bedroom_Coils_Flag[i] = 1;
                   }
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
                    if ((MasterDB.EC_Saloon_Registers_Flag[i] == 0)&& (MasterDB.EC_Saloon_Registers[i] != register_buffer[i])){
                        MasterDB.EC_Saloon_Registers_Flag[i] = 1;
                        MasterDB.EC_Saloon_Registers[i] = register_buffer[i];
                    }

                break;
            case COILS:
                //Write to EC Saloon Coils
                for (i=0; i <= (COIL_ENVC_MAX - COILS_ENVC_BASE); i++)
                    if ((MasterDB.EC_Saloon_Coils_Flag[i] == 0) && (MasterDB.EC_Saloon_Coils[i] != coil_buffer[i])){
                        MasterDB.EC_Saloon_Coils[i] = coil_buffer[i];
                        MasterDB.EC_Saloon_Coils_Flag[i] = 1;
                    }
            break;

            }
            break;

        }
        break;

    case GENERAL_BOARD:
        switch (slavename) {
        case GENERAL_ENGINE:
            switch (addresstype) {
            case REGISTERS:
                for (i = REG_ANALOG_IN12 - 1; i<= (REG_GENERAL_MAX - REG_ANALOG_IN12); i++)
                    if ((MasterDB.General_Engine_Registers_Flag[i] == 0) && ( MasterDB.General_Engine_Registers[i]!= register_buffer[i])){
                        MasterDB.General_Engine_Registers_Flag[i] = 1;
                         MasterDB.General_Engine_Registers[i] = register_buffer[i];
                    }

                break;
            case COILS:
                for (i= 0; i <= (COIL_GENERAL_MAX - COILS_GENERAL_BASE); i++)
                    if ((MasterDB.General_Engine_Coils_Flag[i]== 0) && ( MasterDB.General_Engine_Coils[i] != coil_buffer[i])) {
                        MasterDB.General_Engine_Coils_Flag[i]= 1;
                        MasterDB.General_Engine_Coils[i] = coil_buffer[i];
                    }
                break;
            default:
                //SHOULDNT HAPPEN
                break;
            }
        }

        break;


    case LCD_CONTROL:
        switch (slavename) {
            case BEDROOM:
                switch (addresstype) {
                case ENGINE:
                    for (i=0; i <= (REG_ENG_MAX - ENGINE_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Engine_Flag[i] == 0) && (MasterDB.LCD_Saloon_Engine[i] != register_buffer[i])){
                            MasterDB.LCD_Saloon_Engine_Flag[i] = 1;
                         MasterDB.LCD_Saloon_Engine[i] = register_buffer[i];
                        }
                    break;
                case DCSYS:
                    for (i=0; i<= (REG_DCSYS_MAX - DCSYSTEM_BASE); i++)
                        if ((MasterDB.LCD_Saloon_DCsys_Flag[i] == 0) && (MasterDB.LCD_Saloon_DCsys[i] != register_buffer[i])){
                            MasterDB.LCD_Saloon_DCsys_Flag[i] = 1;
                            MasterDB.LCD_Saloon_DCsys[i] = register_buffer[i];
                        }
                    break;
                case ACSYS:
                    for (i=0; i<= (REG_ACSYS_MAX - ACSYSTEM_BASE); i++)
                        if ((MasterDB.LCD_Saloon_ACsys_Flag[i] == 0) && (MasterDB.LCD_Saloon_ACsys[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_ACsys_Flag[i] = 1;
                        MasterDB.LCD_Saloon_ACsys[i] = register_buffer[i];
                        }
                    break;
                case HVAC:
                    for (i=0; i<= (REG_HVAC_MAX - HVAC_BASE); i++)
                        if ((MasterDB.LCD_Saloon_HVAC_Flag[i]== 0) && (MasterDB.LCD_Saloon_HVAC[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_HVAC[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_HVAC_Flag[i] = 1;
                        }
                    break;
                case TANKS:
                    for (i=0; i<= (REG_TANKS_MAX - TANKS_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Tanks_Flag[i]== 0) && (MasterDB.LCD_Saloon_Tanks[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Tanks[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_Tanks_Flag[1] = 1;
                        }
                    break;
                case RR:
                    for (i=0; i<= (REG_RR_MAX - RR_BASE); i++)
                        if ((MasterDB.LCD_Saloon_RR_Flag[i] ==0) && (MasterDB.LCD_Saloon_RR[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_RR[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_RR_Flag[i] = 1;
                        }
                    break;
                case GPS:
                    for (i=0; i <= (REG_GPS_MAX - GPS_BASE); i++)
                        if ((MasterDB.LCD_Saloon_GPS_Flag[i] == 0) && (MasterDB.LCD_Saloon_GPS[i] != register_buffer[i])){
                            MasterDB.LCD_Saloon_GPS_Flag[1] = 1;
                            MasterDB.LCD_Saloon_GPS[i] = register_buffer[i];
                        }

                    break;
                case SONAR:
                    for (i=0; i<= (REG_SONAR_MAX - SONAR_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Sonar_Flag[i] == 0) && (MasterDB.LCD_Saloon_Sonar[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Sonar[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_Sonar_Flag[i] = 1;
                        }
                    break;
                case LIGHTS:
                    for (i=0; i<= (REG_LIGHTS_MAX - LIGHTS_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Lights_Flag[i] ==0) && (MasterDB.LCD_Saloon_Lights[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Lights[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_Lights_Flag[i]=1;
                        }
                    break;
                case LCD:
                    for (i=0; i<= (REG_LCD_MAX - LCD_BASE); i++)
                        if ((MasterDB.LCD_Saloon_LCD_Flag[i] == 0) && (MasterDB.LCD_Saloon_LCD[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_LCD_Flag[i] = 1;
                        MasterDB.LCD_Saloon_LCD[i] = register_buffer[i];
                        }
                    break;
                case GYRO:
                    for (i=0; i<= (REG_GYRO_MAX - GYRO_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Gyro_Flag[i] == 0) && (MasterDB.LCD_Saloon_Gyro[i] != register_buffer[i])){
                            MasterDB.LCD_Saloon_Gyro_Flag[i] = 1;
                        MasterDB.LCD_Saloon_Gyro[i] = register_buffer[i];
                        }
                    break;
                case ALARM:
                    for (i=0; i<= (COIL_ALRM_MAX - ALARMS_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Alarm_Flag[i] == 0) && (MasterDB.LCD_Saloon_Alarm[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Alarm[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_Alarm_Flag[i] =1;
                        }
                    break;
                case WARNING:
                    for (i=0; i<= (COIL_WARN_MAX - WARNINGS_BASE); i++)
                        if ((MasterDB.LCD_Saloon_Warning_Flag[i]== 0) && (MasterDB.LCD_Saloon_Warning[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Warning[i] = register_buffer[i];
                        MasterDB.LCD_Saloon_Warning_Flag[i] = 1;
                        }
                    break;
                default:
                    //SHOULDN'T HAPPEN
                    break;
                    }

            break;
            case SALOON:
            switch (addresstype) {
            case ENGINE:
                for (i=0; i <= (REG_ENG_MAX - ENGINE_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Engine_Flag[i] == 0) && (MasterDB.LCD_Saloon_Engine[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Engine_Flag[i] = 1;
                     MasterDB.LCD_Saloon_Engine[i] = register_buffer[i];
                    }
                break;
            case DCSYS:
                for (i=0; i<= (REG_DCSYS_MAX - DCSYSTEM_BASE); i++)
                    if ((MasterDB.LCD_Saloon_DCsys_Flag[i] == 0) && (MasterDB.LCD_Saloon_DCsys[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_DCsys_Flag[i] = 1;
                        MasterDB.LCD_Saloon_DCsys[i] = register_buffer[i];
                    }
                break;
            case ACSYS:
                for (i=0; i<= (REG_ACSYS_MAX - ACSYSTEM_BASE); i++)
                    if ((MasterDB.LCD_Saloon_ACsys_Flag[i] == 0) && (MasterDB.LCD_Saloon_ACsys[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_ACsys_Flag[i] = 1;
                    MasterDB.LCD_Saloon_ACsys[i] = register_buffer[i];
                    }
                break;
            case HVAC:
                for (i=0; i<= (REG_HVAC_MAX - HVAC_BASE); i++)
                    if ((MasterDB.LCD_Saloon_HVAC_Flag[i]== 0) && (MasterDB.LCD_Saloon_HVAC[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_HVAC[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_HVAC_Flag[i] = 1;
                    }
                break;
            case TANKS:
                for (i=0; i<= (REG_TANKS_MAX - TANKS_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Tanks_Flag[i]== 0) && (MasterDB.LCD_Saloon_Tanks[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_Tanks[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_Tanks_Flag[1] = 1;
                    }
                break;
            case RR:
                for (i=0; i<= (REG_RR_MAX - RR_BASE); i++)
                    if ((MasterDB.LCD_Saloon_RR_Flag[i] ==0) && (MasterDB.LCD_Saloon_RR[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_RR[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_RR_Flag[i] = 1;
                    }
                break;
            case GPS:
                for (i=0; i <= (REG_GPS_MAX - GPS_BASE); i++)
                    if ((MasterDB.LCD_Saloon_GPS_Flag[i] == 0) && (MasterDB.LCD_Saloon_GPS[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_GPS_Flag[1] = 1;
                        MasterDB.LCD_Saloon_GPS[i] = register_buffer[i];
                    }

                break;
            case SONAR:
                for (i=0; i<= (REG_SONAR_MAX - SONAR_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Sonar_Flag[i] == 0) && (MasterDB.LCD_Saloon_Sonar[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_Sonar[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_Sonar_Flag[i] = 1;
                    }
                break;
            case LIGHTS:
                for (i=0; i<= (REG_LIGHTS_MAX - LIGHTS_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Lights_Flag[i] ==0) && (MasterDB.LCD_Saloon_Lights[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_Lights[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_Lights_Flag[i]=1;
                    }
                break;
            case LCD:
                for (i=0; i<= (REG_LCD_MAX - LCD_BASE); i++)
                    if ((MasterDB.LCD_Saloon_LCD_Flag[i] == 0) && (MasterDB.LCD_Saloon_LCD[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_LCD_Flag[i] = 1;
                    MasterDB.LCD_Saloon_LCD[i] = register_buffer[i];
                    }
                break;
            case GYRO:
                for (i=0; i<= (REG_GYRO_MAX - GYRO_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Gyro_Flag[i] == 0) && (MasterDB.LCD_Saloon_Gyro[i] != register_buffer[i])){
                        MasterDB.LCD_Saloon_Gyro_Flag[i] = 1;
                    MasterDB.LCD_Saloon_Gyro[i] = register_buffer[i];
                    }
                break;
            case ALARM:
                for (i=0; i<= (COIL_ALRM_MAX - ALARMS_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Alarm_Flag[i] == 0) && (MasterDB.LCD_Saloon_Alarm[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_Alarm[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_Alarm_Flag[i] =1;
                    }
                break;
            case WARNING:
                for (i=0; i<= (COIL_WARN_MAX - WARNINGS_BASE); i++)
                    if ((MasterDB.LCD_Saloon_Warning_Flag[i]== 0) && (MasterDB.LCD_Saloon_Warning[i] != register_buffer[i])){
                    MasterDB.LCD_Saloon_Warning[i] = register_buffer[i];
                    MasterDB.LCD_Saloon_Warning_Flag[i] = 1;
                    }
                break;
            default:
                //SHOULDN'T HAPPEN
                break;
                }

        break;
      default:
      //SHOULDNT HAPPEN
      break;
            }
         }
    return 1;
    }
}
