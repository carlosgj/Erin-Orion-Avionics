#include "ADC.h"

void ADC_init(void){
    //FVR config
    FVRCONbits.ADFVR = 0b10; //2.048
    FVRCONbits.EN = TRUE;
    
    FVRCONbits.TSEN = TRUE;
    FVRCONbits.TSRNG = TRUE;
    
    //ADC config
    ADCON0bits.FM = TRUE;
    ADREFbits.PREF = 0b11;
    ADCLK = 0b011111;
    
    ADCON0bits.ON = TRUE;
}

uint8_t ADC_getReading(uint8_t channel, uint16_t *value){
    *value = 0;
    ADPCH = channel;

    uint16_t tempVal = 0;
    
    ADCON0bits.ADGO = TRUE;
    while(ADCON0bits.ADGO){
    }
    
    tempVal = ((uint16_t)ADRESH << 8);
    tempVal |= ADRESL;
        
    *value += tempVal;
    
    return ADC_SUCCESS;
}