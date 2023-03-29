#ifndef DIGITALIO_H
#define	DIGITALIO_H

#include <xc.h> 
#include "common.h"

union buttonState_t{
    uint8_t all;
    struct{
        unsigned button0 :1;
        unsigned button1 :1;
        unsigned button2 :1;
        unsigned button3 :1;
        unsigned button4 :1;
        unsigned button5 :1;
        unsigned button6 :1;
        unsigned button7 :1;
    };
} buttonState, buttonChangeState;

uint8_t buttonHoldTimes[5];

void button_init(void);
void updateInputs(void);

#endif	/* XC_HEADER_TEMPLATE_H */

