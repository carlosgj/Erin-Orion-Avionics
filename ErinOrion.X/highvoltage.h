#ifndef HIGHVOLTAGE_H
#define	HIGHVOLTAGE_H

#include <xc.h> 
#include "common.h"
#include "time.h"

#define HV_ON_TIME      (5000)
#define HV_LOCKOUT_TIME (60000)

uint16_t HVOnTime = 0; //monoMillis when HV was turned on
uint16_t HVOffTime = 0; //monoMillis when HV was turned off

uint8_t HVState = FALSE;
uint8_t HVLockout = TRUE;

void HV_init(void);
void HV_periodic(void);
void HV_requestOn(void);

#endif	/* XC_HEADER_TEMPLATE_H */

