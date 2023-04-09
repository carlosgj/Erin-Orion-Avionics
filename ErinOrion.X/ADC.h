#ifndef ADC_H
#define	ADC_H

#include <xc.h> 
#include "common.h"

#define ADC_SUCCESS 0

void ADC_init(void);
uint8_t ADC_getReading(uint8_t channel, uint16_t *value);

#endif


