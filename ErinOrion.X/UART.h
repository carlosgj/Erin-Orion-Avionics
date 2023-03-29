#ifndef RS422_H
#define	RS422_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "common.h"
#include "commConstants.h"
#include "FIFO.h"

void UART_init(void);
void UART_write(uint8_t theByte);

void debug_UART_init(void);
void putch(unsigned char theByte);

#endif

