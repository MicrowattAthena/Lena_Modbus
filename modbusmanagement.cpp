#include <modbusmanagement.h>
#include <masterdb.h>
#include <stdlib.h>
#include <modbusprotocols.h>
#include <LCD/lcd_registers.h>
#include <General/general_registers.h>
#include <EC/EC_registers.h>

extern "C" {

//Sets up and Connects Modbus
int initialisemodbus(void){

    initialiseRTU();
    setRTUmode();
    settimeouts();
    if (RTU_connect()==1){
        return 1;
    }else{
        return 0;
    }

}

int testread(void){
    setmodbusslave(1);
    readaddresses(256,10);

    return 1;
    }

int readLCDslave(int IDnumber, char slavename){

    //Attempts to read from each block of registers
    //If successful, writes the read buffer to master DB
    setmodbusslave((IDnumber));

    if (readaddresses(ENGINE_BASE -1,REG_ENG_MAX - ENGINE_BASE))
       writeDB(LCD_CONTROL,slavename, ENGINE);
    if (readaddresses(DCSYSTEM_BASE - 1,REG_DCSYS_MAX - DCSYSTEM_BASE))
       writeDB(LCD_CONTROL,slavename, DCSYS );
    if (readaddresses(ACSYSTEM_BASE - 1,REG_ACSYS_MAX - ACSYSTEM_BASE))
       writeDB(LCD_CONTROL,slavename, ACSYS);
    if (readaddresses(HVAC_BASE - 1,REG_HVAC_MAX - HVAC_BASE))
       writeDB(LCD_CONTROL,slavename, HVAC);
    if (readaddresses(TANKS_BASE- 1,REG_TANKS_MAX - TANKS_BASE))
       writeDB(LCD_CONTROL,slavename,TANKS );
    if (readaddresses(RR_BASE- 1,REG_RR_MAX - RR_BASE))
       writeDB(LCD_CONTROL,slavename, RR);
    if (readaddresses(GPS_BASE- 1,REG_GPS_MAX -GPS_BASE))
       writeDB(LCD_CONTROL,slavename,GPS );
    if (readaddresses(SONAR_BASE- 1,REG_SONAR_MAX - SONAR_BASE))
       writeDB(LCD_CONTROL,slavename,SONAR );
    if (readaddresses(LIGHTS_BASE- 1,REG_LIGHTS_MAX-LIGHTS_BASE))
       writeDB(LCD_CONTROL,slavename,LIGHTS );
    if (readaddresses(LCD_BASE- 1,REG_LCD_MAX - LCD_BASE))
       writeDB(LCD_CONTROL,slavename,LCD );
    if (readaddresses(GYRO_BASE- 1,REG_GYRO_MAX - GYRO_BASE))
       writeDB(LCD_CONTROL,slavename,GYRO );
    if (readcoils(ALARMS_BASE- 1,COIL_ALRM_MAX - ALARMS_BASE))
       writeDB(LCD_CONTROL,slavename,ALARM );
    if (readcoils(WARNINGS_BASE- 1,COIL_WARN_MAX - WARNINGS_BASE))
       writeDB(LCD_CONTROL,slavename,WARNING );
    return 1;
}

int readgeneralslave(int IDnumber, char slavename){
    setmodbusslave(IDnumber);
  if (readaddresses(REGS_GENERAL_BASE- 1, REG_GENERAL_MAX - REGS_GENERAL_BASE))
       writeDB(GENERAL_BOARD,slavename,REGISTERS);
   if (readcoils(COILS_GENERAL_BASE- 1,COIL_GENERAL_MAX - COILS_GENERAL_BASE))
       writeDB(GENERAL_BOARD,slavename,COILS);
    return 1;
}

int readECslave(int IDnumber, char slavename){

    setmodbusslave(IDnumber);
   if (readaddresses(REGS_ENVC_BASE- 1,REG_ENVC_MAX - REGS_ENVC_BASE))
       writeDB(ENVIRONMENTAL_CONTROL,slavename,REGISTERS);
   if (readcoils(COILS_ENVC_BASE- 1,COIL_ENVC_MAX - COILS_ENVC_BASE))
       writeDB(ENVIRONMENTAL_CONTROL,slavename,COILS);
    return 1;
}

int writeLCDtime(int IDNumber){
    setmodbusslave(IDNumber);
    //Construct RTC write buffers
    //Write to LCDS
    return 1;
}

}
