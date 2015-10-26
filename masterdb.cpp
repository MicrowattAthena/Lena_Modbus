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

struct register_construct
{
    char slavetype; char slavename; char addresstype; int address;
};
struct linked_registers
{
    struct register_construct LCD_register;
    struct register_construct nonLCD_register;
};



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
  struct queuefile GUIqueuefile[42];
   int queuecounter = 0;

   struct linked_registers Linked_DB[50];
   int linkedlength;

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


  qWarning() << "Reading Generals";
    for (int i = 0; GeneralSlaveIDs[i] !=0;i++)
        readgeneralslave(GeneralSlaveIDs[i],GeneralSlaveName[i]);

  qWarning() << "Reading ECs";
    for (int i = 0; ECSlaveIDs[i] != 0; i++)
        readECslave(ECSlaveIDs[i],ECSlaveName[i]);
    qWarning() << "Reading LCDs";
     for (int i = 0; LCDSlaveIDs[i] != 0;i++)
          //pass ID to modbusmanagement
          readLCDslave(LCDSlaveIDs[i],LCDSlaveName[i]);


    return 1;
}


int managelcd() {
    //Most of the LCD Data is obtained from other slave devices.
    //The program needs to set the correct values to the LCD DB and then rewrite to the LCDs.

    buildlcdDB();
    managelcdalarms();
    return 1;
}

int managelcdalarms()
{  //Alarms also need to be monitored. Check Alarm States and set alarm if necessary


    return 1;
}
int buildlcdDB()
{
    /*This needs to check the flags set when reading from DB.
    //For a Linked Variable:
    //If neither value has been changed, nothing must be done
    //If both values have changed (should occur on first read OR if a change has occured in GUI), nothing must be done
    //If one value has changed (i.e. it has been overwritten outside the program),
     this changed value must be written to the other slave */

    //For some reason the senddatatoGUI function causes the program to crash. The function runs fine, but when it attempts to
    //to return to this function, it fails. However, it works fine when called from a different function (?)
    int i; int lcdflag; int nonlcdflag;
    uint buffer;

    for (i = 0; i <=linkedlength; i++){

        lcdflag = (sendflagofDB(Linked_DB[i].LCD_register.slavetype,Linked_DB[i].LCD_register.slavename,
                                Linked_DB[i].LCD_register.addresstype, Linked_DB[i].LCD_register.address));

        nonlcdflag = (sendflagofDB(Linked_DB[i].nonLCD_register.slavetype,Linked_DB[i].nonLCD_register.slavename,
                                   Linked_DB[i].nonLCD_register.addresstype, Linked_DB[i].nonLCD_register.address));

     /*   if (lcdflag ^ nonlcdflag)
        {
            qWarning()<< "Non-Matching Linked!";
            qWarning()<< nonlcdflag;
            if (lcdflag)
            {

                senddatatoGUI(Linked_DB[i].LCD_register.slavetype,Linked_DB[i].LCD_register.slavename,
                                        Linked_DB[i].LCD_register.addresstype,Linked_DB[i].LCD_register.address);
                    qWarning()<< buffer;
              writequeue(Linked_DB[i].nonLCD_register.slavetype,Linked_DB[i].nonLCD_register.slavename,
                           Linked_DB[i].nonLCD_register.addresstype, Linked_DB[i].nonLCD_register.address,buffer);

            }else{
                qWarning()<<i;
                buffer = senddatatoGUI(Linked_DB[i].nonLCD_register.slavetype,Linked_DB[i].nonLCD_register.slavename,
                                       Linked_DB[i].nonLCD_register.addresstype,Linked_DB[i].nonLCD_register.address);
                writequeue(Linked_DB[i].LCD_register.slavetype,Linked_DB[i].LCD_register.slavename,
                           Linked_DB[i].LCD_register.addresstype, Linked_DB[i].LCD_register.address, buffer);

            }
        } */
    }


    return 1;
}

int initialiseLCDlinks()
{

    // Creates a link betweeen LCD registers and other registers
    //To be completed - Will test with ENV/LCD First

 /*   Linked_DB[0].LCD_register  = {LCD_CONTROL,SALOON,DCSYS,REG_DCSYS_STARTBATTVOLT - DCSYSTEM_BASE};
    Linked_DB[0].nonLCD_register= {GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_ANALOG_IN13 - REGS_GENERAL_BASE};

    Linked_DB[1].LCD_register = {LCD_CONTROL,SALOON,DCSYS,REG_DCSYS_SRVBATTVOLT - DCSYSTEM_BASE};
    Linked_DB[1].nonLCD_register = {GENERAL_BOARD,GENERAL_ENGINE,REGISTERS,REG_ANALOG_IN12 - REGS_GENERAL_BASE};
*/
    Linked_DB[0].LCD_register = {LCD_CONTROL,SALOON,HVAC,REG_HVAC_SALNSETTEMP};
    Linked_DB[0].nonLCD_register = {ENVIRONMENTAL_CONTROL,SALOON,REGISTERS, REG_ROOM_TEMPR_THRESH};
    linkedlength = 0;
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
        queuecounter +=1;
        qWarning() << "Adding Value to Queue";

        GUIqueuefile[queuecounter].slavetype = slavetype;
         GUIqueuefile[queuecounter].slavename = slavename;
          GUIqueuefile[queuecounter].addresstype = addresstype;
           GUIqueuefile[queuecounter].address = address;
            GUIqueuefile[queuecounter].value = value;


    }

}

void deletequeuedata () {
    qWarning()<< "Deleting Queue";
    int i;
    for (i = 0; i<= queuecounter; i++)
    {
        GUIqueuefile[i].address = 0;
        GUIqueuefile[i].addresstype = 0;
        GUIqueuefile[i].slavename = 0;
        GUIqueuefile[i].slavetype = 0;
    }

    queuecounter = 0;
}

void processqueue(){

    // Writes queue files to slaves, and checks if the addresses are linked.
    // If so, it also writes the value to the linked address.
    // NEEDS TO BE TESTED
    qWarning()<< "Processing Queue";

    uint i; uint y;
    qWarning()<< queuecounter;
    for (i = queuecounter;i > 0; i--)
    {    
        qWarning()<< GUIqueuefile[i].addresstype;
        qWarning()<< GUIqueuefile[i].slavetype;
    writequeue(GUIqueuefile[i].slavetype, GUIqueuefile[i].slavename, GUIqueuefile[i].addresstype, GUIqueuefile[i].address,GUIqueuefile[i].value);
        for (y = 0; y <=linkedlength; y++)
        {

         if (GUIqueuefile[i].slavetype == LCD_CONTROL)
            {
             qWarning()<<"Checking for link in LCD CONTROL";
              if ((GUIqueuefile[i].addresstype == Linked_DB[y].LCD_register.addresstype) && (GUIqueuefile[i].address == Linked_DB[y].LCD_register.address))
                {
                 qWarning() << "Link in LCD Control found!";
                 writequeue(Linked_DB[y].nonLCD_register.slavetype, Linked_DB[y].nonLCD_register.slavename,
                            Linked_DB[y].nonLCD_register.addresstype, Linked_DB[y].nonLCD_register.address, GUIqueuefile[i].value);
                }
          }else{
            qWarning()<< "Checking for link in nonLCD CONTROL";

            if ((GUIqueuefile[i].addresstype == Linked_DB[y].nonLCD_register.addresstype) && (GUIqueuefile[i].address == Linked_DB[y].nonLCD_register.address))
                {
                 qWarning() << "Link in NONLCD Control found!";
                 writequeue(Linked_DB[y].LCD_register.slavetype, Linked_DB[y].LCD_register.slavename,
                            Linked_DB[y].LCD_register.addresstype, Linked_DB[y].LCD_register.address, GUIqueuefile[i].value);
                 }
            }
        }

    }
    deletequeuedata();
}

int writequeue(char slavetype, char slavename, char addresstype, int address, int value) {
    //First update internal DB

    updateDB(slavetype,slavename, addresstype,address,value);
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
                qWarning()<< "Writing to LCD 1";
                             qWarning() << address -1;
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
         qWarning()<< "Writing to LCD 1";
                      qWarning() << address -1;
        write_single_register(address - 1,value);
        break;
    break;
    }

}
return 0;
}
int sendflagofDB(char slavetype, char slavename, char addresstype, int address) {
    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:

        switch (slavename) {
        case BEDROOM:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.EC_Bedroom_Registers_Flag[address -1];
            case COILS:
                return MasterDB.EC_Bedroom_Coils_Flag[address - 1];
            break;
            }

         case SALOON:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.EC_Saloon_Registers_Flag[address - 1];
            case COILS:
                return MasterDB.EC_Saloon_Coils_Flag[address - 1];
            break;
            }
        }

    case GENERAL_BOARD:

        switch (slavename){
        case GENERAL_ENGINE:
            switch (addresstype) {
            case REGISTERS:
                return MasterDB.General_Engine_Registers_Flag[address - 1];
            case COILS:
                return MasterDB.General_Engine_Coils_Flag[address - 1];
            break;
        }


    break;
    }




    case LCD_CONTROL:

            switch (addresstype) {
            case ENGINE:
                return MasterDB.LCD_Saloon_Engine_Flag[address - 1];
            case DCSYS:
                return MasterDB.LCD_Saloon_DCsys_Flag[address - 1];
            case ACSYS:
                return MasterDB.LCD_Saloon_ACsys_Flag[address - 1];
            case HVAC:
                return MasterDB.LCD_Saloon_HVAC_Flag[address - 1];
            case TANKS:
                return MasterDB.LCD_Saloon_Tanks_Flag[address -1];
            case RR:
                return MasterDB.LCD_Saloon_RR_Flag[address - 1];
            case GPS:
                return MasterDB.LCD_Saloon_GPS_Flag[address - 1];
            case SONAR:
                return MasterDB.LCD_Saloon_Sonar_Flag[address - 1];
            case LIGHTS:
                return MasterDB.LCD_Saloon_Lights_Flag[address - 1];
            case LCD:
                return MasterDB.LCD_Saloon_LCD_Flag[address - 1];
            case GYRO:
                return MasterDB.LCD_Saloon_Gyro_Flag[address - 1];
            break;
            }


}
return 0;
}

int senddatatoGUI(char slavetype, char slavename, char addresstype, int address) {
    // The will return some information from the DB.
    
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
//                qWarning()<<"Accessing Registers";

  //              qWarning()<< MasterDB.EC_Saloon_Registers[address - 1];
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

int updateDB(char slavetype, char slavename, char addresstype, int address, int value)
{
    // Updates a single value in the internal DB.

    switch (slavetype) {
    case ENVIRONMENTAL_CONTROL:
        switch (slavename) {
        case BEDROOM:
            switch (addresstype) {
            case REGISTERS:
                //write to EC Bedroom registers
                MasterDB.EC_Bedroom_Registers[address - REGS_ENVC_BASE] = value;
                break;
            case COILS:
                //Write to EC Bedroom Coils
                   MasterDB.EC_Bedroom_Coils[address - COILS_ENVC_BASE] = value;
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
                   MasterDB.EC_Saloon_Registers[address - REGS_ENVC_BASE] = value;

                break;
            case COILS:
                //Write to EC Saloon Coils
                MasterDB.EC_Saloon_Coils[address - COILS_ENVC_BASE] = value;
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
                   MasterDB.General_Engine_Registers[address - REGS_GENERAL_BASE] = value;
                break;
            case COILS:
                   MasterDB.General_Engine_Coils[address - COILS_GENERAL_BASE] = value;
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
                    MasterDB.LCD_Saloon_Engine[address - ENGINE_BASE] = value;
                    break;
                case DCSYS:
                    MasterDB.LCD_Saloon_DCsys[address - DCSYSTEM_BASE] = value;

                    break;
                case ACSYS:
                     MasterDB.LCD_Saloon_ACsys[address - ACSYSTEM_BASE] = value;
                    break;
                case HVAC:
                     MasterDB.LCD_Saloon_HVAC[address - HVAC_BASE] = value;
                    break;
                case TANKS:
                     MasterDB.LCD_Saloon_Tanks[address - TANKS_BASE] = value;
                    break;
                case RR:
                   MasterDB.LCD_Saloon_RR[address - RR_BASE] = value;
                    break;
                case GPS:
                 MasterDB.LCD_Saloon_GPS[address - GPS_BASE] = value;
                    break;
                case SONAR:
                     MasterDB.LCD_Saloon_Sonar[address - SONAR_BASE] = value;
                    break;
                case LIGHTS:
                     MasterDB.LCD_Saloon_Lights[address - LIGHTS_BASE] = value;
                    break;
                case LCD:
                   MasterDB.LCD_Saloon_LCD[address - LCD_BASE] = value;
                    break;
                case GYRO:
                    MasterDB.LCD_Saloon_Gyro[address - GYRO_BASE] = value;
                    break;
                case ALARM:
                    MasterDB.LCD_Saloon_Alarm[address - ALARMS_BASE] = value;
                    break;
                case WARNING:
                     MasterDB.LCD_Saloon_Warning[address - WARNINGS_BASE] = value;
                    break;
                default:
                    //SHOULDN'T HAPPEN
                    break;
                    }

            break;
            case SALOON:
            switch (addresstype) {
            case ENGINE:
                MasterDB.LCD_Saloon_Engine[address - ENGINE_BASE] = value;
                break;
            case DCSYS:
                MasterDB.LCD_Saloon_DCsys[address - DCSYSTEM_BASE] = value;

                break;
            case ACSYS:
                 MasterDB.LCD_Saloon_ACsys[address - ACSYSTEM_BASE] = value;
                break;
            case HVAC:
                 MasterDB.LCD_Saloon_HVAC[address - HVAC_BASE] = value;
                break;
            case TANKS:
                 MasterDB.LCD_Saloon_Tanks[address - TANKS_BASE] = value;
                break;
            case RR:
               MasterDB.LCD_Saloon_RR[address - RR_BASE] = value;
                break;
            case GPS:
             MasterDB.LCD_Saloon_GPS[address - GPS_BASE] = value;
                break;
            case SONAR:
                 MasterDB.LCD_Saloon_Sonar[address - SONAR_BASE] = value;
                break;
            case LIGHTS:
                 MasterDB.LCD_Saloon_Lights[address - LIGHTS_BASE] = value;
                break;
            case LCD:
               MasterDB.LCD_Saloon_LCD[address - LCD_BASE] = value;
                break;
            case GYRO:
                MasterDB.LCD_Saloon_Gyro[address - GYRO_BASE] = value;
                break;
            case ALARM:
                MasterDB.LCD_Saloon_Alarm[address - ALARMS_BASE] = value;
                break;
            case WARNING:
                 MasterDB.LCD_Saloon_Warning[address - WARNINGS_BASE] = value;
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


int writeDB(char slavetype, char slavename, char addresstype){

    int i;
// Switch Case Slavetype (EC, General, LCD)
// Switch Case Slave Identifier (Location)
// Switch Case Register Type
// Writes Register and Coil Buffers to Master Database if value has not changed before
// Also sets a flag if the value is new
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
