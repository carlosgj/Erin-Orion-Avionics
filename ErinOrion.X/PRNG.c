#include "PRNG.h"

void PRNG_Init(void){
    PRNGLatestFull = get16BitParam(PARAM_PRNG_SEED_L);
}

void PRNG_Periodic(void){
    PRNG_Iterate();
    PRNGLatestSmall = (uint8_t)(PRNGLatestFull >> 8);
    //printf("%u\n", PRNGLatestFull);
}

void PRNG_Iterate(void){
    uint16_t newVal = PRNGLatestFull;
    newVal *= get16BitParam(PARAM_PRNG_MULT_L);
    newVal += get16BitParam(PARAM_PRNG_INC_L);
    
    if(params[PARAM_PRNG_USE_TEMP]){
        uint16_t temperature;
        ADC_getReading(0b00111100, &temperature);
        //printf("Temp: 0x%X\n", temperature);
        newVal += (temperature & 0b111);
    }
    
    PRNGLatestFull = newVal;    
}