#ifndef PRNG_H
#define	PRNG_H

#include <xc.h> 
#include "common.h"

uint16_t PRNGLatestFull;
uint8_t PRNGLatestSmall;

void PRNG_Init(void);
void PRNG_Periodic(void);
void PRNG_Iterate(void);

#endif	/* XC_HEADER_TEMPLATE_H */

