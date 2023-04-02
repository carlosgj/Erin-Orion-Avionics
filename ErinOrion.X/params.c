#include "params.h"

void write_param(uint8_t index, uint8_t value){
    params[index] = value;
    params_comp[index] = ~value;
}

uint8_t loadParamsFromProgram(void){
    uint8_t i;
    for(i=0; i<NUM_PARAMS; i++){
        write_param(i, programValues[i]);
    }
    return PARAM_LOAD_SUCCESS;
}

void burnParamsToEEPROM(void){
    uint8_t i;
    
    for(i=0; i<NUM_PARAMS; i++){
        EEPROM_write(PARAM_EEP_START+i, params[i]);
        EEPROM_write(PARAM_COMP_EEP_START+i, ~params[i]);
    }
}

uint8_t loadParamsFromEEPROM(void){
    uint8_t i;
    uint8_t norm, comp;
    
    for(i=0; i<NUM_PARAMS; i++){
        norm = EEPROM_read(PARAM_EEP_START+i);
        comp = EEPROM_read(PARAM_COMP_EEP_START+i);
        //printf("%X, %X, %X\n", norm, comp, (uint8_t)(~comp));
        if(norm == (uint8_t)(~comp)){
            //Good!
            write_param(i, norm);
        }
        else{
            return PARAM_LOAD_FAIL;
        }
    }
    return PARAM_LOAD_SUCCESS;
}

uint8_t paramScrub(void){
    uint8_t normal, comp;
    
    for(paramScrubLocation=0; paramScrubLocation<NUM_PARAMS; paramScrubLocation++){
        normal = params[paramScrubLocation];
        comp = ~params_comp[paramScrubLocation];
        
        if(normal != comp){
            return PARAM_SCRUB_FAIL;
        }
    }
    
    return PARAM_SCRUB_SUCCESS;
}

uint16_t get16BitParam(uint8_t index){
    return (((uint16_t)params[index+1]) << 8) | params[index];
}