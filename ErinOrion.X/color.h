#ifndef COLOR_H
#define	COLOR_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);

#endif	/* XC_HEADER_TEMPLATE_H */

