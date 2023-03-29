#include "params.h"

void loadParamsFromProgram(void){
    
}

uint8_t loadParamsFromEEPROM(void){
    
    return PARAM_LOAD_SUCCESS;
}

uint8_t paramScrub(void){
    uint8_t normal, comp;
    
    for(paramScrubLocation=0; paramScrubLocation<NUM_PARAMS; paramScrubLocation++){
        normal = params[paramScrubLocation];
        comp = ~params[paramScrubLocation];
        
        if(normal != comp){
            return PARAM_SCRUB_FAIL;
        }
    }
    
    return PARAM_SCRUB_SUCCESS;
}