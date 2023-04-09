#include "digitalIO.h"

void button_init(void){
    buttonState.all = 0;
    buttonChangeState.all = 0;
    
    //Setup pins
    TRISAbits.TRISA0 = INPUT;
    TRISAbits.TRISA1 = INPUT;
    TRISAbits.TRISA2 = INPUT;
    TRISAbits.TRISA3 = INPUT;
    TRISAbits.TRISA4 = INPUT;
    TRISAbits.TRISA5 = INPUT;
}

void updateInputs(void){
    static uint8_t counter = 0;
    union buttonState_t newInputs;
    
    newInputs.all = (PORTA & 0b00111111);
    
    if(counter == 10){
        //printf("Button state: 0x%02x\n", newInputs.all);
        counter = 0;
    }
    counter++;
    
    buttonChangeState.all = newInputs.all & (~buttonState.all);
    
    buttonState.all = newInputs.all;
    
    uint8_t i;
    for(i=0; i<6; i++){
        if((buttonState.all & (1<<i)) == 0 ){
            //Button is not pressed
            buttonHoldTimes[i] = 0;
        }
        else{
            //Button is pressed
            buttonHoldTimes[i]++;
        }
    }
}