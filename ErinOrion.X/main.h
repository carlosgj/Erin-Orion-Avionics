#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include <string.h>
#include "config.h"
#include "common.h"
#include "UART.h"
#include "time.h"
#include "SerialManager.h"
#include "gitVersion.h"
#include "digitalIO.h"
#include "highvoltage.h"
#include "TLC5947.h"
#include "thrusters.h"
#include "params.h"
#include "PRNG.h"
#include "NeoPixel.h"

#define WDT_CHECK_GOOD 0x11

#define MAIN_LOOP_TIME  (50)

uint16_t cycleSlack;
uint16_t minCycleSlack = 0xffff;

void init(void);
void periodicTasks(void);
void getResetCause(void);

#endif