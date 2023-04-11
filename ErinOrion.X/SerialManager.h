#ifndef SERIALMANAGER_H
#define	SERIALMANAGER_H

#include <xc.h> 
#include <stdlib.h>
#include "common.h"
#include "HDLC.h"
#include "UART.h"
#include "commConstants.h"
#include "TLC5947.h"
#include "highvoltage.h"

union controlByte_t {
    uint8_t byte;
    struct{
        unsigned chan :3;
        unsigned type :2;
        unsigned address :3;
    };
};

void dbgSerialPeriodic(void);

uint8_t currentMessageIdx = 0;
uint8_t currentMessage[20];

#endif

