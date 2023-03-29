#ifndef PARAMS_H
#define	PARAMS_H

#include <xc.h> 
#include "common.h"

#define NUM_PARAMS      (32)

#define PARAM_LOAD_SUCCESS    (0)

#define PARAM_SCRUB_SUCCESS (0)
#define PARAM_SCRUB_FAIL    (1)

#define PARAM_HV_ON_DURATION_L      (0)
#define PARAM_HV_ON_DURATION_H      (1)
#define PARAM_HV_LOCKOUT_DURATION_L (2)
#define PARAM_HV_LOCKOUT_DURATION_H (3)

uint8_t params[NUM_PARAMS] __at(0x800);
uint8_t params_comp[NUM_PARAMS] __at(0x900);

uint8_t paramScrubLocation;

const uint8_t programValues[] = {};


void loadParamsFromProgram(void);
uint8_t loadParamsFromEEPROM(void);
uint8_t paramScrub(void);

#endif	/* XC_HEADER_TEMPLATE_H */

