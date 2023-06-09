#ifndef THRUSTERS_H
#define	THRUSTERS_H

#include <xc.h> 
#include "common.h"
#include "TLC5947.h"
#include "PRNG.h"
#include "time.h"

#define MAIN_THRUSTER_LED_INDEX_1     (18)
#define MAIN_THRUSTER_LED_INDEX_2     (19)
#define MAIN_THRUSTER_LED_INDEX_3     (20)

#define MANEUVER_OFFSET     (100)

#define MAN_STATE_OFF       (0)
#define MAN_STATE_RAMPUP    (1)
#define MAN_STATE_ON        (2)
#define MAN_STATE_RAMPDOWN  (3)
#define MAN_STATE_LOCKOUT   (4)

uint8_t rcsState = 0;

uint8_t maneuver = FALSE;

uint8_t maneuverState = MAN_STATE_LOCKOUT;

void thrusters_init(void);
void thrusters_periodic(void);

#endif	/* XC_HEADER_TEMPLATE_H */

