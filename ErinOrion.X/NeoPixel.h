#ifndef NEOPIXEL_H
#define	NEOPIXEL_H

#include <xc.h> 
#include "common.h"

uint8_t NeoPixelData[4] __at(0x601);

void NeoPixel_init(void);
extern void NeoPixel_sendData(void);

#endif	/* XC_HEADER_TEMPLATE_H */

