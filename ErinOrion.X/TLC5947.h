#ifndef TLC5947_H
#define	TLC5947_H

#include <xc.h> 
#include "common.h"

uint16_t LEDBrightness[24];

void TLC5947_init(void);
void TLC5947_write(void);
void TLC5947_periodic(void);

#endif	/* XC_HEADER_TEMPLATE_H */

