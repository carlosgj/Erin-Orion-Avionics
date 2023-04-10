#ifndef TLC5947_H
#define	TLC5947_H

#include <xc.h> 
#include "common.h"

#define BUTTON0_RED     (0)
#define BUTTON0_GREEN   (1)
#define BUTTON0_BLUE    (2)

#define BUTTON1_RED     (5)
#define BUTTON1_GREEN   (4)
#define BUTTON1_BLUE    (3)

#define BUTTON2_RED     (8)
#define BUTTON2_GREEN   (7)
#define BUTTON2_BLUE    (6)

#define BUTTON3_RED     (11)
#define BUTTON3_GREEN   (10)
#define BUTTON3_BLUE    (9)

#define BUTTON4_RED     (14)
#define BUTTON4_GREEN   (13)
#define BUTTON4_BLUE    (12)

uint8_t LEDBrightness[24];

void TLC5947_init(void);
void TLC5947_write(void);
void TLC5947_periodic(void);

#endif	/* XC_HEADER_TEMPLATE_H */

