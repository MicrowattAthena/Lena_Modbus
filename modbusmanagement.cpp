#include <modbusmanagement.h>
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
    if (RTU_connect()==0){
        return 0;
    }else{
        return -1;
    }

}

//Reads Data from all slaves and stores internally

int testread(void){
    setmodbusslave(1);
    readaddresses(256,10);

    return 0;
    }

int readLCDslave(int IDnumber){
    setmodbusslave((IDnumber));

    //Do something with each read!
    readaddresses(ENGINE_BASE,REG_ENG_MAX - ENGINE_BASE);
    readaddresses(DCSYSTEM_BASE,REG_DCSYS_MAX - DCSYSTEM_BASE);
    readaddresses(ACSYSTEM_BASE,REG_ACSYS_MAX - ACSYSTEM_BASE);
    readaddresses(HVAC_BASE,REG_HVAC_MAX - HVAC_BASE);
    readaddresses(TANKS_BASE,REG_TANKS_MAX - TANKS_BASE);
    readaddresses(RR_BASE,REG_RR_MAX - RR_BASE);
    readaddresses(GPS_BASE,REG_GPS_MAX -GPS_BASE);
    readaddresses(SONAR_BASE,REG_SONAR_MAX - SONAR_BASE);
    readaddresses(LIGHTS_BASE,REG_LIGHTS_MAX-LIGHTS_BASE);
    readaddresses(LCD_BASE,REG_LCD_MAX - LCD_BASE);
    readaddresses(RTC_BASE,REG_RTC_LCD_MAX - RTC_BASE);
    readaddresses(GYRO_BASE,REG_GYRO_MAX - GYRO_BASE);
    readcoils(ALARMS_BASE,COIL_ALRM_MAX - ALARMS_BASE);
    readcoils(WARNINGS_BASE,COIL_WARN_MAX - WARNINGS_BASE);
    return 0;
}

int readgeneralslave(int IDnumber){
    setmodbusslave(IDnumber);

    readaddresses(REGS_GENERAL_BASE, REG_GENERAL_MAX - REGS_GENERAL_BASE);
    readcoils(COILS_GENERAL_BASE,COIL_GENERAL_MAX - COILS_GENERAL_BASE);
    //Do Something with each read!
    return 0;
}

int readECslave(int IDnumber){
    setmodbusslave(IDnumber);

    readaddresses(REGS_ENVC_BASE,REG_ENVC_MAX - REGS_ENVC_BASE);
    readcoils(COILS_ENVC_BASE,COIL_ENVC_MAX - COILS_ENVC_BASE);

    //Do something with each read!
    return 0;
}


}
