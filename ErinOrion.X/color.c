#include <xc.h>
#include "color.h"

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder;
    unsigned int p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43u;
    remainder = (hsv.h - (region * 43u)) * 6u; 

    p = (hsv.v * (255u - hsv.s)) >> 8u;
    q = (hsv.v * (255u - ((hsv.s * (unsigned int)remainder) >> 8u))) >> 8u;
    t = (hsv.v * (255u - ((hsv.s * (unsigned int)(255u - remainder)) >> 8u))) >> 8u;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}
