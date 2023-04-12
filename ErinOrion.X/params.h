#ifndef PARAMS_H
#define	PARAMS_H

#include <xc.h> 
#include "common.h"
#include "EEPROM.h"

#define NUM_PARAMS      (32)

#define PARAM_EEP_START         (0x0)
#define PARAM_COMP_EEP_START    (0x200)

#define PARAM_LOAD_SUCCESS    (0)
#define PARAM_LOAD_FAIL       (1)

#define PARAM_SCRUB_SUCCESS (0)
#define PARAM_SCRUB_FAIL    (1)

#define PARAM_HV_ON_DURATION_L      (0)
#define PARAM_HV_ON_DURATION_H      (1)
#define PARAM_HV_LOCKOUT_DURATION_L (2)
#define PARAM_HV_LOCKOUT_DURATION_H (3)
#define PARAM_PRNG_MULT_L           (4)
#define PARAM_PRNG_MULT_H           (5)
#define PARAM_PRNG_INC_L            (6)
#define PARAM_PRNG_INC_H            (7)
#define PARAM_PRNG_SEED_L           (8)
#define PARAM_PRNG_SEED_H           (9)
#define PARAM_PRNG_USE_TEMP         (10)
#define PARAM_THRUST_RAMPUP_TIME    (11)
#define PARAM_THRUST_RAMPUP_INC     (12)
#define PARAM_THRUST_RAMPDWN_TIME   (13)
#define PARAM_THRUST_RAMPDWN_INC    (14)
#define PARAM_RCS_IDLE_ON_PRB       (15)
#define PARAM_RCS_IDLE_OFF_PRB      (16)
#define PARAM_RCS_MAN_ON_PRB        (17)
#define PARAM_RCS_MAN_OFF_PRB       (18)
#define PARAM_MAN_PROB              (19)
#define PARAM_MAN_LOCKOUT_L         (20)
#define PARAM_MAN_LOCKOUT_H         (21)
#define PARAM_MAN_MIN_TIME          (22)
#define PARAM_MAN_OFF_PROB          (23)
#define PARAM_CLR_BTN_WHITE_R       (24)
#define PARAM_CLR_BTN_WHITE_G       (25)
#define PARAM_CLR_BTN_WHITE_B       (26)
#define PARAM_CLR_BTN_ORANGE_R      (27)
#define PARAM_CLR_BTN_ORANGE_G      (28)
#define PARAM_CLR_BTN_ORANGE_B      (29)
#define PARAM_RCS_NIGHT_ON_PRB      (30)
#define PARAM_NIGHT_MODE_SHIFT      (31)


uint8_t params[NUM_PARAMS] __at(0x800);
uint8_t params_comp[NUM_PARAMS] __at(0x900);

uint8_t paramScrubLocation;

const uint8_t programValues[] = {
    0x88,   //HV on duration (ms) low byte 
    0x13,   //HV on duration (ms) high byte
    0x30,   //HV lockout duration (ms) low byte
    0x75,   //HV lockout duration (ms) high byte
    0x09,   //PRNG multiplier low byte
    0x00,   //PRNG multiplier high byte
    0xEF,   //PRNG increment low byte
    0x1E,   //PRNG increment high byte
    0xAA,   //PRNG seed low byte
    0xAA,   //PRNG seed high byte
    1,      //PRNG add temperature bits on each iteration
    42,     //Thruster manuever rampup time
    6,      //Thruster maneuver rampup increment
    42,     //Thruster manuever rampdown time
    20,      //Thruster maneuver rampdown increment
    3,      //RCS idle mode turnon probability
    20,     //RCS idle mode turnoff probability
    32,     //RCS maneuver mode turnon probability
    50,     //RCS maneuver mode turnoff probability
    255,    //Maneuver start probability
    200,    //Maneuver lockout time low byte
    0,      //Maneuver lockout time high byte
    100,    //Maneuver minimum on-time (in cycles)
    4,      //Maneuver stop probability
    100,    //Button white red amount
    200,    //Button white green amount
    255,    //Button white blue amount
    200,    //Button orange red amount
    255,    //Button orange green amount
    0,      //Button orange blue amount
    2,      //RCS night mode turnon probability
    3,      //Night mode brightness rightshift bits
};

void write_param(uint8_t index, uint8_t value);
uint8_t loadParamsFromProgram(void);
uint8_t loadParamsFromEEPROM(void);
void burnParamsToEEPROM(void);
uint8_t paramScrub(void);
uint16_t get16BitParam(uint8_t index);

#endif	/* XC_HEADER_TEMPLATE_H */

