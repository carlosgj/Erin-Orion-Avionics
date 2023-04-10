#ifndef UI_H
#define UI_H

#include <xc.h> 
#include "common.h"
#include "highvoltage.h"
#include "digitalIO.h"
#include "TLC5947.h"
#include "color.h"
#include "NeoPixel.h"
#include "thrusters.h"

#define UI_STATE_NORMAL     (0)
#define UI_STATE_FLOOD      (1)

#define FLOOD_STATE_OFF     (0)
#define FLOOD_STATE_RED     (1)
#define FLOOD_STATE_GREEN   (2)
#define FLOOD_STATE_BLUE    (3)
#define FLOOD_STATE_WHITE   (4)
#define FLOOD_STATE_RAINBOW (5)

uint8_t UIState = UI_STATE_NORMAL;

uint8_t FloodState = FLOOD_STATE_OFF;
uint8_t CabinState = FALSE;

void UI_init(void);
void UI_periodic(void);

#endif