#include <modbusmanagement.h>
#include <masterdb.h>
#include <stdlib.h>
#include <modbusprotocols.h>
#include <LCD/lcd_registers.h>
#include <General/general_registers.h>
#include <EC/EC_registers.h>
#include <time.h>
#include <QDebug>

extern "C" {

//Sets up and Connects Modbus
int initialisemodbus(void){

    int retries = 0;
    initialiseRTU();
    //setdebugmode();
    setRTUmode();
    settimeouts();

    do {
        if (RTU_connect()){
            return 1;
        }else{
            retries++;
        }
    } while (retries <= 4);

    return 0;
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
   // Different Engine Variations have different readable addresses.
   // for example, engine does not use ADC channels 1-8.
    switch (slavename) {
    case GENERAL_ENGINE:
        if (readaddresses(REG_ANALOG_IN12 - 1, REG_GENERAL_MAX - REG_ANALOG_IN12))
             writeDB(GENERAL_BOARD,slavename,REGISTERS);
         if (readcoils(COILS_GENERAL_BASE- 1,COIL_GENERAL_MAX - COILS_GENERAL_BASE))
             writeDB(GENERAL_BOARD,slavename,COILS);
        break;

    default:
        break;
    }
    return 1;
}

int readECslave(int IDnumber, char slavename){

    setmodbusslave(IDnumber);
   if (readaddresses(REGS_ENVC_BASE- 1,REG_ENVC_MAX - REGS_ENVC_BASE))
   {
        qWarning() << "EC Register Read Successful - Writing to DB";
        writeDB(ENVIRONMENTAL_CONTROL,slavename,REGISTERS);
   }else{
       // qWarning() << "EC Read Failed";
   }
   if (readcoils(COILS_ENVC_BASE- 1,COIL_ENVC_MAX - COILS_ENVC_BASE))
   {
        qWarning() << "EC Coil Read Successful - Writing to DB";
        writeDB(ENVIRONMENTAL_CONTROL,slavename,COILS);
   }else{
      //  qWarning() << "EC Read Failed";
   }
    return 1;
}

int writeLCDRTU(int IDNumber){

    uint16_t rtcbuffer[7];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    setmodbusslave(IDNumber);
    rtcbuffer[0] = tm.tm_sec;
    rtcbuffer[1] = tm.tm_min;
    rtcbuffer[2] = tm.tm_hour;
    rtcbuffer[3] = tm.tm_mday;
    rtcbuffer[4] = tm.tm_mon + 1;
    rtcbuffer[5] = tm.tm_year + 1900;
    rtcbuffer[6] = 1;
    write_registers(RTC_BASE -1,7, rtcbuffer);
    return 1;
}

int writegeneralRTU(int IDNumber){
    uint16_t rtcbuffer[7];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    setmodbusslave(IDNumber);
    rtcbuffer[0] = tm.tm_sec;
    rtcbuffer[1] = tm.tm_min;
    rtcbuffer[2] = tm.tm_hour;
    rtcbuffer[3] = tm.tm_mday;
    rtcbuffer[4] = tm.tm_mon + 1;
    rtcbuffer[5] = tm.tm_year + 1900;
    rtcbuffer[6] = 1;

    write_registers(REG_RTC_GEN_SECS -1,7, rtcbuffer);
}
}
