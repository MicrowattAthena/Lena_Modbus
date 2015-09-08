#ifndef LCD_MODBUS_REGS_H
#define LCD_MODBUS_REGS_H

//-----------------------------------------------------------------------------
// Holding register address space
//-----------------------------------------------------------------------------

#define MAKE_REG(comp, offset)  (((comp) << 8) | (offset))

#define ENGINE_BASE    MAKE_REG(0x01, 0x00)
#define DCSYSTEM_BASE  MAKE_REG(0x02, 0x00)
#define ACSYSTEM_BASE  MAKE_REG(0x03, 0x00)
#define HVAC_BASE      MAKE_REG(0x04, 0x00)
#define TANKS_BASE     MAKE_REG(0x05, 0x00)
#define RR_BASE        MAKE_REG(0x06, 0x00)
#define GPS_BASE       MAKE_REG(0x07, 0x00)
#define SONAR_BASE     MAKE_REG(0x08, 0x00)
#define LIGHTS_BASE    MAKE_REG(0x09, 0x00)
#define LCD_BASE       MAKE_REG(0x0a, 0x00)
#define RTC_BASE       MAKE_REG(0x0b, 0x00)
#define GYRO_BASE      MAKE_REG(0x0c, 0x00)


// ENGINE registers
typedef enum {
    REG_ENG_PRSENSOR = ENGINE_BASE,             // Pressure sensor
    REG_ENG_TEMPSENSOR,                         // Temperature sensor
    REG_ENG_ALTERNATOR,                         // Alternator
    REG_ENG_ENGRUNNING,                         // Engine running
    REG_ENG_MORSPOSL,                           // Morse position (linear)
    REG_ENG_MORSPOSM,                           // Morse position (micro switches)
    REG_ENG_HPRALRM,                            // High pressure alarm
    REG_ENG_LPRALRM,                            // Low pressure alarm
    REG_ENG_HITEMPALRM,                         // High temperature alarm
    REG_ENG_HITEMPWARN,                         // High temperature warning
    REG_ENG_ENGSTART,                           // Start/Stop engine
    REG_ENG_MAX
} EngineRegs;

// DC_SYSTEM registers
typedef enum {
    REG_DCSYS_ALT1CURRENT = DCSYSTEM_BASE,      // Alternator 1 current
    REG_DCSYS_ALT2CURRENT,                      // Alternator 2 current
    REG_DCSYS_STARTCHRGALTCUR,                  // Starter Charge Alt current
    REG_DCSYS_STARTCHRGCHRGCUR,                 // Starter Charge chrg current
    REG_DCSYS_BATTCURRENT,                      // Battery current
    REG_DCSYS_ALTBATTCURR,                      // Alternator battery current
    REG_DCSYS_DISTCURRENT,                      // Distribution current
    REG_DCSYS_DISTFRGCURR,                      // Dist fridge current
    REG_DCSYS_DISTL1CURR,                       // Dist Lights 1 current
    REG_DCSYS_DISTL2CURR,                       // Dist Lights 2 current
    REG_DCSYS_WATERPUMP,                        // Water pump
    REG_DCSYS_RADTVCURR,                        // Dist Radio & TV current
    REG_DCSYS_SHWRPUMP,                         // Shower pump
    REG_DCSYS_12VSOCK,                          // 12V sockets
    REG_DCSYS_HORN,                             // Horn
    REG_DCSYS_WC,                               // W.C.
    REG_DCSYS_STARTBATTVOLT,                    // Starter battery voltage
    REG_DCSYS_SRVBATTVOLT,                      // Services battery voltage
    REG_DCSYS_SRVBATTCAP,                       // Services battery capacity remaining
    REG_DCSYS_INVERTERON,                       // Inverter On/Off
    REG_DCSYS_INVERTERFAULT,                    // Inverter fault
    REG_DCSYS_CHARGERBULK,                      // Charger bulk
    REG_DCSYS_CHARGERABSORB,                    // Charger absorption
    REG_DCSYS_CHARGERFLOAT,                     // Charger float
    REG_DCSYS_INVERTLOWBATT,                    // Inverter low battery
    REG_DCSYS_INVERTOVERLOAD,                   // Inverter overload
    REG_DCSYS_INVERTOVERTEMP,                   // Inverter over temperature
    REG_DCSYS_EXTERNLIGHTLEV,                   // EXternal light level
    REG_DCSYS_INTRUDEDET,                       // Intruder detection
    REG_DCSYS_BILGEPUMPRUN,                     // Bilge pump run
    REG_DCSYS_BILGEPUMPSECD,                    // Bilge pump sec/day
    REG_DCSYS_SRVBATTCHARGE,                    // Services Battery charging
    REG_DCSYS_INVERTSTART,                      // Inverter On/Off
    REG_DCSYS_STARTBATLNK,                      // Starter battery link
    REG_DCSYS_SRVBATTLOWCAPALRM,                // Services battery low capacity alarm
    REG_DCSYS_MAX
} DcSystemRegs;

// AC_SYSTEM registers
typedef enum {
    REG_ACSYS_SHOREPWRAVAIL = ACSYSTEM_BASE,    // Shower power available
    REG_ACSYS_ACVOLTAGE,                        // AC voltage
    REG_ACSYS_ACPOWER,                          // AC power
    REG_ACSYS_SHOREPWR,                         // AC shore power
    REG_ACSYS_PWRRNGMAIN,                       // AC power ring main
    REG_ACSYS_MAX
} AcSystemRegs;

// HVAC registers
typedef enum {
    REG_HVAC_FLOWTEMP = HVAC_BASE,              // Flow temperature
    REG_HVAC_RETURNTEMP,                        // Return temperature
    REG_HVAC_CLRFTOPTEMP,                       // Calorifier top temperature
    REG_HVAC_CLRFMIDTEMP,                       // Calorifier middle temperature
    REG_HVAC_CLRFBOTTEMP,                       // Calorifier bottom temperature
    REG_HVAC_OUTTEMP,                           // Outside temperature
    REG_HVAC_OUTHUMID,                          // Outside humidity
    REG_HVAC_SALNTEMP,                          // Saloon temperature
    REG_HVAC_SALNHUMID,                         // Saloon humidity
    REG_HVAC_MSBEDTEMP,                         // Master bedroom temperature
    REG_HVAC_MSBEDHUMID,                        // Master bedroom humidity
    REG_HVAC_BATHTEMP,                          // Bathroom temperature
    PRM_HVAC_HEATINGON,                         // Heating ON/OFF status
    PRM_HVAC_COMMSON,                           // Comms ON/OFF status
    REG_HVAC_WBSTRUNSIG ,                       // Webasto run signal
    REG_HVAC_RUNHEATOVERRIDE,                   // Run heating for 1 hour override
    REG_HVAC_SALNSETTEMP,                       // Set saloon temperature
    REG_HVAC_MSBEDSETTEMP,                      // Set master bedroom temperature
    REG_HVAC_BATHSETTEMP,                       // Set bathroom temperature
    REG_HVAC_RADFANSSAL1,                       // Radiator fans saloon 1
    REG_HVAC_RADFANSSAL2,                       // Radiator fans saloon 2
    REG_HVAC_RADFANSBED,                        // Radiator fans bedroom
    REG_HVAC_HEATINGSTART,                      // Start/Stop Heating
    REG_HVAC_COMMSSTART,                        // Start/Stop Comms
    REG_HVAC_MAX
} HvacRegs;

// TANKS registers
typedef enum {
    REG_TANKS_POTWATSTATUS = TANKS_BASE,        // Potable water status
    REG_TANKS_WSWATSTATUS,                      // Waste status
    REG_TANKS_WSFILLSTATUS,                     // Waste filler status
    REG_TANKS_FUELSTATUS,                       // Fuel status
    REG_TANKS_FUELALARM,                        // Fuel alarm threshold
    REG_TANKS_POTWATALARM,                      // Potable water alarm threshold
    REG_TANKS_POTWATWARN,                       // Potable water warning threshold
    REG_TANKS_WSWATALARM,                       // Waste water alarm threshold
    REG_TANKS_WSFILLALARM,                      // Waste filler alarm threshold
    REG_TANKS_MAX
} TanksRegs;

// R&R registers
typedef enum {
    REG_RR_RADIOCD = RR_BASE,                   // Radio CD/DAB
    REG_RR_MAX
} RrRegs;

// GPS registers
typedef enum {
    REG_GPS_LATITUDE_H = GPS_BASE,              // GPS Latitude (high word)
    REG_GPS_LATITUDE_L,                         // GPS Latitude (low word)
    REG_GPS_LONGITUDE_H,                        // GPS Longitude (high word)
    REG_GPS_LONGITUDE_L,                        // GPS Longitude (low word)
    REG_GPS_MAX
} GpsRegs;

// SONAR registers
typedef enum {
    REG_SONAR_AHEAD = SONAR_BASE,               // Ahead
    REG_SONAR_AHEADPORT,                        // Ahead port
    REG_SONAR_AHEADSTARB,                       // Ahead starboard
    REG_SONAR_ASTERN,                           // Astern
    REG_SONAR_ASTERNPORT,                       // Astern port
    REG_SONAR_ASTERNSTARB,                      // Astern starboard
    REG_SONAR_MAX
} SonarRegs;

// LIGHTING registers
typedef enum {
    REG_LIGHTS_TAFTRLIGHT = LIGHTS_BASE,        // Taft rail lights
    REG_LIGHTS_ENGROOMLIGHT,                    // Engine room light
    REG_LIGHTS_BOWLIGHTS,                       // Bow lights
    REG_LIGHTS_NAVLIGHTS,                       // Navigation lights
    REG_LIGHTS_STRIPRED,                        // Saloon strip lights red
    REG_LIGHTS_STRIPGREEN,                      // Saloon strip lights green
    REG_LIGHTS_STRIPBLUE,                       // Saloon strip lights blue
    REG_LIGHTS_GALLEYLT1,                       // Galley light 1
    REG_LIGHTS_GALLEYLT2,                       // Galley light 2
    REG_LIGHTS_SALOONLT1,                       // Saloon light 1
    REG_LIGHTS_SALOONLT2,                       // Saloon light 2
    REG_LIGHTS_SALOONLT3,                       // Saloon light 3
    REG_LIGHTS_SALOONLT4,                       // Saloon light 4
    REG_LIGHTS_SALOONLT5,                       // Saloon light 5
    REG_LIGHTS_SALOONLT6,                       // Saloon light 6
    REG_LIGHTS_SALOONLT7,                       // Saloon light 7
    REG_LIGHTS_SALOONLT8,                       // Saloon light 8
    REG_LIGHTS_BATHLT1,                         // Bathroom light 1
    REG_LIGHTS_BATHLT2,                         // Bathroom light 2
    REG_LIGHTS_MASTERBEDLT1,                    // Master bedroom light 1
    REG_LIGHTS_MASTERBEDLT2,                    // Master bedroom light 2
    REG_LIGHTS_MASTERBEDLT3,                    // Master bedroom light 3
    REG_LIGHTS_MASTERBEDLT4,                    // Master bedroom light 4
    REG_LIGHTS_UPDATEMOOD,                      // Update selected light mood
    REG_LIGHTS_MOODTOUPDATE,                    // Index of mood to update
    REG_LIGHTS_APPLYMOOD,                       // Apply selected light mood
    REG_LIGHTS_MOODTOAPPLY,                     // Index of mood to apply
    REG_LIGHTS_MAX
} LightingRegs;

// LCD registers
typedef enum {
    REG_LCD_ACCEPTALARMS = LCD_BASE,            // Accept alarms
    REG_LCD_STDBYDISP,                          // Active standby display ID
    REG_LCD_MAX
} LCDRegs;

// RTC registers
typedef enum {
    REG_RTC_LCD_SECS = RTC_BASE,                    // Seconds (0-59)
    REG_RTC_LCD_MINS,                               // Minutes (0-59)
    REG_RTC_LCD_HOURS,                              // Hours (0-23)
    REG_RTC_LCD_DAY,                                // Day of the month (1-31)
    REG_RTC_LCD_MONTH,                              // Month (1-12)
    REG_RTC_LCD_YEAR,                               // Year
    REG_RTC_LCD_APPLY,                              // Apply RTC settings
    REG_RTC_LCD_MAX
} RTCRegs;

// GYRO registers
typedef enum {
    REG_GYRO_ROLL = GYRO_BASE,                  // Roll
    REG_GYRO_MAX
} GyroRegs;


//-----------------------------------------------------------------------------
// Coils address space
//-----------------------------------------------------------------------------

#define ALARMS_BASE     MAKE_REG(0x01, 0x00)
#define WARNINGS_BASE   MAKE_REG(0x02, 0x00)

// Alarm coils
typedef enum {
    COIL_ALRM_HIGHPRESS = ALARMS_BASE,          // Engine high pressure
    COIL_ALRM_HIGHTEMP,                         // Engine high temperature
    COIL_ALRM_ERR509,                           // Engine ERR: 509
    COIL_ALRM_POTWATERLOW,                      // Potable water low
    COIL_ALRM_WASTEWATHIGH,                     // Waste water high
    COIL_ALRM_WASTEFILLLOW,                     // Waste filler low
    COIL_ALRM_INVFAULT,                         // Inverter fault
    COIL_ALRM_INVLOWBAT,                        // Inverter low battery
    COIL_ALRM_INVOVERLOAD,                      // Inverter overload
    COIL_ALRM_INVOVERTEMP,                      // Inverter over temperature
    COIL_ALRM_BILGEPUMP,                        // Bilge pump run long
    COIL_ALRM_MAX
} AlarmCoils;

// Warning coils
typedef enum {
    COIL_WARN_HIGHTEMP = WARNINGS_BASE,         // Engine high temperature
    COIL_WARN_POTWATERLOW,                      // Potable water low
    COIL_WARN_WASTEFILLLOW,                     // Waste filler low
    COIL_WARN_MAX
} WarningCoils;

#endif
