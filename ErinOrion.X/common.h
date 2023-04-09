#ifndef COMMON_H
#define	COMMON_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "FIFO.h"
#include "params.h"

#define BOARD_ADDRESS (1)

//######### Debug options ###########

//Uncomment AT MOST ONE of the following to send signals to the test point
//#define LOOPOUT
//#define MSOUT

//###################################

#define TRUE 1
#define FALSE 0

#define INPUT 1
#define OUTPUT 0

#define _XTAL_FREQ (64000000)

#define SW_VER_STR "0.0.1"

#define LED3LAT LATCbits.LATC2
#define LED4LAT LATCbits.LATC3
#define X3LAT LATCbits.LATC5


#define INTEN (INTCON0bits.GIE = TRUE)
#define INTDIS (INTCON0bits.GIE = FALSE)

#define STATUS_LEN (11)
union status_t {
    unsigned char all[STATUS_LEN];
    struct{
        uint8_t unhandledIntCount;
        uint8_t lastUnhandledInt;
        uint8_t loopOverruns;
        uint16_t seconds;
        uint8_t resetCause;
    };
} status;

enum ResetCause {
    RS_POR  = 1,
    RS_BOR  = 2,
    RS_MCLR = 3,
    RS_WDT  = 4,
    RS_WIN  = 5,
    RS_RST  = 6,
    RS_SO   = 7,
    RS_SU   = 8,
    RS_DP   = 9,
    RS_VREG = 10,
    RS_MEM  = 11,
    RS_INVALID = 0
};

FIFO DbgUARTRxBuf;

enum ResetCause resetCause = RS_INVALID;

uint16_t wdtCheckWord = 0;

void fatal(const char * message);
void printf_bin(uint8_t val);

#endif

