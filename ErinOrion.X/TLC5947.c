#include "TLC5947.h"

void TLC5947_init(void){
    //Set up pins
    TRISBbits.TRISB2 = OUTPUT; //Dat
    
    TRISBbits.TRISB3 = OUTPUT; //SCLK
    
    TRISBbits.TRISB4 = OUTPUT; //Blank
    LATBbits.LATB4 = FALSE;
    
    TRISBbits.TRISB5 = OUTPUT; //LAT
    LATBbits.LATB5 = TRUE;
    
    uint8_t i;
    for(i=0; i<24; i++){
        LEDBrightness[i] = 0;
    }
    TLC5947_write();
    LATBbits.LATB4 = TRUE;
}

void TLC5947_write(void){
    uint8_t ledIdx, bitIdx;
    //Start with MSB of output 23
    for(ledIdx=23; ledIdx<254; ledIdx--){
        for(bitIdx=11; bitIdx<254; bitIdx--){
            LATBbits.LATB3 = TRUE;
            __delay_us(50);
            if(((LEDBrightness[ledIdx] >> bitIdx)&0b1) == 0){
                LATBbits.LATB2 = TRUE;
            }
            else{
                LATBbits.LATB2 = FALSE;
            }
            LATBbits.LATB3 = FALSE;
            __delay_us(50);
        }
        
    }
    LATBbits.LATB5 = FALSE;
    __delay_us(50);
    LATBbits.LATB5 = TRUE;
}

void TLC5947_periodic(void){
    
}