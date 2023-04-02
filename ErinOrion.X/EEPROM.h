#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> 
#include "common.h"

uint8_t EEPROM_read(uint16_t addr);
void EEPROM_write(uint16_t addr, uint8_t data);

#endif	/* XC_HEADER_TEMPLATE_H */

