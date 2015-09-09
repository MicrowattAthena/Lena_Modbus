#include "masterdb.h"
#include "modbusmanagement.h"
#include "modbusprotocols.h"
#include "EC/EC_registers.h"
#include "LCD/lcd_registers.h"
extern "C" {

//0 is the terminating character - illegal modbus data address.

    const int LCDSlaveIDs[] = { 1,2, 0 };
    const char LCDSlaveName[] = { SALOON, BEDROOM, '0' };

    const int GeneralSlaveIDs[] = { 0 };
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

   int LCD_Bedroom_Engine[REG_ENG_MAX - ENGINE_BASE];
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
   int LCD_Bedroom_Warning[COIL_WARN_MAX - WARNINGS_BASE];

};

struct database MasterDB;

int initialiseDB () {
//create master Database

    // check slave ids and types of slave
   for (int i = 0; LCDSlaveIDs[i] != 0;i++)
        //pass ID to modbusmanagement
        //Set RTC for each LCD Slave
        readLCDslave(LCDSlaveIDs[i],LCDSlaveName[i]);

    for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
        readgeneralslave(GeneralSlaveIDs[i],GeneralSlaveName[i]);

    for (int i = 0; ECSlaveIDs[i] != 0; i++)
        readECslave(ECSlaveIDs[i],ECSlaveName[i]);


    return 1;
}


int writeDB(char slavetype, char slavename, char addresstype){

    int i;
// Switch Case Slavetype (EC, General, LCD)
// Switch Case Slave Identifier (Location)
// Switch Case Register Type
// Writes Register and Coil Buffers to Master Database
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
        //code TO DO!
        break;


    case LCD_CONTROL:
        switch (slavename) {
            case BEDROOM:
                switch (addresstype) {
                case ENGINE:
                    for (i=0; i <= (REG_ENG_MAX - ENGINE_BASE); i++)
                         MasterDB.LCD_Bedroom_Engine[i] = register_buffer[i];
                    break;
                case DCSYS:
                    for (i=0; i<= (REG_DCSYS_MAX - DCSYSTEM_BASE); i++)
                         MasterDB.LCD_Bedroom_DCsys[i] = register_buffer[i];
                    break;
                case ACSYS:
                    for (i=0; i<= (REG_ACSYS_MAX - ACSYSTEM_BASE); i++)
                        MasterDB.LCD_Bedroom_ACsys[i] = register_buffer[i];
                    break;
                case HVAC:
                    for (i=0; i<= (REG_HVAC_MAX - HVAC_BASE); i++)
                        MasterDB.LCD_Bedroom_HVAC[i] = register_buffer[i];
                    break;
                case TANKS:
                    for (i=0; i<= (REG_TANKS_MAX - TANKS_BASE); i++)
                        MasterDB.LCD_Bedroom_Tanks[i] = register_buffer[i];
                    break;
                case RR:
                    for (i=0; i<= (REG_RR_MAX - RR_BASE); i++)
                        MasterDB.LCD_Bedroom_RR[i] = register_buffer[i];
                    break;
                case GPS:
                    for (i=0; i <= (REG_GPS_MAX - GPS_BASE); i++)
                        MasterDB.LCD_Bedroom_GPS[i] = register_buffer[i];
                    break;
                case SONAR:
                    for (i=0; i<= (REG_SONAR_MAX - SONAR_BASE); i++)
                        MasterDB.LCD_Bedroom_Sonar[i] = register_buffer[i];
                    break;
                case LIGHTS:
                    for (i=0; i<= (REG_LIGHTS_MAX - LIGHTS_BASE); i++)
                        MasterDB.LCD_Bedroom_Lights[i] = register_buffer[i];
                    break;
                case LCD:
                    for (i=0; i<= (REG_LCD_MAX - LCD_BASE); i++)
                        MasterDB.LCD_Bedroom_LCD[i] = register_buffer[i];
                    break;
                case GYRO:
                    for (i=0; i<= (REG_GYRO_MAX - GYRO_BASE); i++)
                        MasterDB.LCD_Bedroom_Gyro[i] = register_buffer[i];
                    break;
                case ALARM:
                    for (i=0; i<= (COIL_ALRM_MAX - ALARMS_BASE); i++)
                        MasterDB.LCD_Bedroom_Alarm[i] = register_buffer[i];
                    break;
                case WARNING:
                    for (i=0; i<= (COIL_WARN_MAX - WARNINGS_BASE); i++)
                        MasterDB.LCD_Bedroom_Warning[i] = register_buffer[i];
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
                     MasterDB.LCD_Saloon_Engine[i] = register_buffer[i];
                break;
            case DCSYS:
                for (i=0; i<= (REG_DCSYS_MAX - DCSYSTEM_BASE); i++)
                     MasterDB.LCD_Saloon_DCsys[i] = register_buffer[i];
                break;
            case ACSYS:
                for (i=0; i<= (REG_ACSYS_MAX - ACSYSTEM_BASE); i++)
                    MasterDB.LCD_Saloon_ACsys[i] = register_buffer[i];
                break;
            case HVAC:
                for (i=0; i<= (REG_HVAC_MAX - HVAC_BASE); i++)
                    MasterDB.LCD_Saloon_HVAC[i] = register_buffer[i];
                break;
            case TANKS:
                for (i=0; i<= (REG_TANKS_MAX - TANKS_BASE); i++)
                    MasterDB.LCD_Saloon_Tanks[i] = register_buffer[i];
                break;
            case RR:
                for (i=0; i<= (REG_RR_MAX - RR_BASE); i++)
                    MasterDB.LCD_Saloon_RR[i] = register_buffer[i];
                break;
            case GPS:
                for (i=0; i <= (REG_GPS_MAX - GPS_BASE); i++)
                    MasterDB.LCD_Saloon_GPS[i] = register_buffer[i];
                break;
            case SONAR:
                for (i=0; i<= (REG_SONAR_MAX - SONAR_BASE); i++)
                    MasterDB.LCD_Saloon_Sonar[i] = register_buffer[i];
                break;
            case LIGHTS:
                for (i=0; i<= (REG_LIGHTS_MAX - LIGHTS_BASE); i++)
                    MasterDB.LCD_Saloon_Lights[i] = register_buffer[i];
                break;
            case LCD:
                for (i=0; i<= (REG_LCD_MAX - LCD_BASE); i++)
                    MasterDB.LCD_Saloon_LCD[i] = register_buffer[i];
                break;
            case GYRO:
                for (i=0; i<= (REG_GYRO_MAX - GYRO_BASE); i++)
                    MasterDB.LCD_Saloon_Gyro[i] = register_buffer[i];
                break;
            case ALARM:
                for (i=0; i<= (COIL_ALRM_MAX - ALARMS_BASE); i++)
                    MasterDB.LCD_Saloon_Alarm[i] = register_buffer[i];
                break;
            case WARNING:
                for (i=0; i<= (COIL_WARN_MAX - WARNINGS_BASE); i++)
                    MasterDB.LCD_Saloon_Warning[i] = register_buffer[i];
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
