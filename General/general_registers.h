//-----------------------------------------------------------------------------
// General board Modbus register map
//-----------------------------------------------------------------------------
#ifndef _GENERAL_MODBUS_REGS_H_
#define _GENERAL_MODBUS_REGS_H_

#define REGS_GENERAL_BASE    1
#define COILS_GENERAL_BASE   1

// Holding registers
typedef enum {
    REG_ANALOG_IN1 = REGS_GENERAL_BASE,
    REG_ANALOG_IN2,
    REG_ANALOG_IN3,
    REG_ANALOG_IN4,
    REG_ANALOG_IN5,
    REG_ANALOG_IN6,
    REG_ANALOG_IN7,
    REG_ANALOG_IN8,
    REG_ANALOG_IN12, // Service Battery Voltage
    REG_ANALOG_IN13, // Starter Battery Voltage
    REG_ANALOG_IN14, // Other Battery Voltage
    REG_ANALOG_IN15, // Service Battery Current
    REG_AIN1_FSD,
    REG_AIN2_FSD,
    REG_AIN3_FSD,
    REG_AIN4_FSD,
    REG_AIN5_FSD,
    REG_AIN6_FSD,
    REG_AIN7_FSD,
    REG_AIN8_FSD,

    REG_BAT_FSD, // Battery Current FSD
    REG_SRV_BAT_CAP, // Not Implemented Yet
    REG_SRV_BAT_LOW_ALRM, // Not Implemented Yet
    REG_SRV_BLG_PMP_SECS, // Not Implemented Yet
    REG_ENG_RUN_MINS, // Not Implemented Yet
    REG_AHR_INOUT_ACC, // Not Implemented Yet

    REG_HEATING_MODE,
    REG_HEATING_THRESH,

    REG_GEN_ENG_MODE,
    REG_ENG_VTHRESH1,
    REG_ENG_VTHRESH2,
    REG_ENG_CURRTHR,
    REG_ENG_RPM_DIV,
    REG_ENG_RPM,

    REG_RTC_GEN_SECS,                    // Seconds (0-59)
    REG_RTC_GEN_MINS,                    // Minutes (0-59)
    REG_RTC_GEN_HOURS,                   // Hours (0-23)
    REG_RTC_GEN_DAY,                     // Day of the month (1-31)
    REG_RTC_GEN_MONTH,                   // Month (1-12)
    REG_RTC_GEN_YEAR,                    // Year
    REG_RTC_GEN_APPLY,                   // Apply RTC settings

    REG_GENERAL_MAX
} GeneralRegs;

// Coils
typedef enum {
    COIL_INPUT1 = COILS_GENERAL_BASE,
    COIL_INPUT2,
    COIL_INPUT3,
    COIL_INPUT4,
    COIL_INPUT5,
    COIL_INPUT6,
    COIL_INPUT7,
    COIL_OUTPUT1,
    COIL_OUTPUT2,
    COIL_OUTPUT3,
    COIL_OUTPUT4,
    COIL_OUTPUT5,
    COIL_OUTPUT6,
    COIL_OUTPUT7,
    COIL_OUTPUT8,
    COIL_CMD_INV_RUN,
    COIL_CMD_FUEL_POL_RUN,
    COIL_FAULT,
    COIL_GENERAL_MAX
} GeneralCoils;

// Map REG_ANALOG_IN* registers to ADC channel
static int regToAdcChan[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    12,
    13,
    14,
    15
};

#endif
