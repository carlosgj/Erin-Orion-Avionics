#include <xc.h>
#include "common.h"

void fatal(const char * message){
    printf("FATAL: %s", message);
    RESET();
}

void printf_bin(uint8_t val){
    uint8_t i;
    for(i=0; i<8; i++){
        //printf("")
        if((val & (1 << (7-i))) != 0){
            printf("1");
        }
        else{
            printf("0");
        }
    }
}
