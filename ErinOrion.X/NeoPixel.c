#include "NeoPixel.h"

void NeoPixel_init(void){
    TRISCbits.TRISC6 = OUTPUT;
    LATCbits.LATC6 = FALSE;
    
    NeoPixelData[0] = 0x00; //White
    NeoPixelData[1] = 0x00; //Blue
    NeoPixelData[2] = 0x00; //Red
    NeoPixelData[3] = 0x00; //Green
}
