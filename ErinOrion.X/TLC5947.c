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
    LATBbits.LATB3 = TRUE; //Start with clock low
    //Start with MSB of output 23
    for(ledIdx=23; ledIdx<24; ledIdx--){
        uint8_t brightness = LEDBrightness[ledIdx];
        if(nightMode){
            brightness >>= params[PARAM_NIGHT_MODE_SHIFT];
        }
        //Clock out 8 real bits
        for(bitIdx=7; bitIdx<8; bitIdx--){
            LATBbits.LATB3 = TRUE; //Clock
            if(((brightness >> bitIdx)&0b1) == 0){
                LATBbits.LATB2 = TRUE;
            }
            else{
                LATBbits.LATB2 = FALSE;
            }
            __delay_us(50);
            LATBbits.LATB3 = FALSE;
            __delay_us(50);
        }
        
        //Clock out 4 zero bits
        LATBbits.LATB2 = TRUE;
        LATBbits.LATB3 = TRUE;
        __delay_us(50);
        LATBbits.LATB3 = FALSE;
        __delay_us(50);
        LATBbits.LATB3 = TRUE;
        __delay_us(50);
        LATBbits.LATB3 = FALSE;
        __delay_us(50);
        LATBbits.LATB3 = TRUE;
        __delay_us(50);
        LATBbits.LATB3 = FALSE;
        __delay_us(50);
        LATBbits.LATB3 = TRUE;
        __delay_us(50);
        LATBbits.LATB3 = FALSE;
        __delay_us(50);
        LATBbits.LATB3 = TRUE;
    }
    
    LATBbits.LATB5 = FALSE;
    __delay_us(100);
    LATBbits.LATB5 = TRUE;
}

void TLC5947_periodic(void){
    
}