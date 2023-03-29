#include "digitalIO.h"

void button_init(void){
    buttonState.all = 0;
    buttonChangeState.all = 0;
}

void updateInputs(void){
    union buttonState_t newInputs;
    newInputs.all = 0;
    
    buttonChangeState.all = newInputs.all & (~buttonState.all);
    
    buttonState.all = newInputs.all;
    
    uint8_t i;
    for(i=0; i<5; i++){        
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