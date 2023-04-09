#ifndef THRUSTERS_H
#define	THRUSTERS_H

#include <xc.h> 
#include "common.h"
#include "TLC5947.h"
#include "PRNG.h"

#define MAIN_THRUSTER_LED_INDEX     (2)

#define MAN_STATE_OFF       (0)
#define MAN_STATE_RAMPUP    (1)
#define MAN_STATE_ON        (2)
#define MAN_STATE_RAMPDOWN  (3)

uint8_t rcsState = 0;

uint8_t maneuver = FALSE;

uint8_t maneuverState = MAN_STATE_OFF;

void thrusters_init(void);
void thrusters_periodic(void);
void thrusters_setState(uint8_t state);

#endif	/* XC_HEADER_TEMPLATE_H */

