//-----------------------------------------------------------------------------
// Environmental Control board Modbus register map
//-----------------------------------------------------------------------------
#ifndef _ENV_CONTROL_MODBUS_REGS_H_
#define _ENV_CONTROL_MODBUS_REGS_H_

#define REGS_ENVC_BASE   1
#define COILS_ENVC_BASE  1

// Holding registers
typedef enum {
    REG_ROOM_TEMPR_THRESH = REGS_ENVC_BASE,
    REG_FLOW_TEMPR_THRESH,
    REG_CO2ALRM_THRESH,
    REG_HUMIHI_THRESH,
    REG_HUMILO_THRESH,
    REG_FANS_MODE,
    REG_FAN_SPEED,
    REG_HEAT_MODE,
    REG__EC_ENG_MODE,
    REG_TEMPLED_TOLER,
    REG_LCD_BRIGHTNESS,
    REG_BLIGHT_TIMEOUT,
    REG_HUMIDITY,
    REG_TEMPR_ROOM,
    REG_TEMPR_WATERFLOW,
    REG_TEMPR_RADOUT,
    REG_TEMPR_AIROUT,
    REG_TEMPR_AIRIN,
    REG_CO2_PPM,
    REG_ENVC_MAX
} EnvCtrlRegs;

// Coils
typedef enum {
    COIL_OCCUPIED = COILS_ENVC_BASE,
    COIL_BOOST,
    COIL_HEATING,
    COIL_ENVC_MAX
} EnvCtrlCoils;

#endif
