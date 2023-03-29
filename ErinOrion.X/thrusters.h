#ifndef THRUSTERS_H
#define	THRUSTERS_H

#include <xc.h> 
#include "common.h"

uint8_t thrusterState = FALSE;

void thrusters_init(void);
void thrusters_setState(uint8_t state);

#endif	/* XC_HEADER_TEMPLATE_H */

