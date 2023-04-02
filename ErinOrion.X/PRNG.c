#include "PRNG.h"

void PRNG_Init(void){
    PRNGLatestFull = get16BitParam(PARAM_PRNG_SEED_L);
}

void PRNG_Periodic(void){
    PRNG_Iterate();
    PRNGLatestSmall = (uint8_t)(PRNGLatestFull >> 8);
    //printf("%u\n", PRNGLatestFull);
    uint16_t i; 
    for(i=0; i<10000; i++){
        asm("NOP");
    }
}

void PRNG_Iterate(void){
    uint16_t temp = PRNGLatestFull;
    temp *= get16BitParam(PARAM_PRNG_MULT_L);
    temp += get16BitParam(PARAM_PRNG_INC_L);
    
    PRNGLatestFull = temp;    
}