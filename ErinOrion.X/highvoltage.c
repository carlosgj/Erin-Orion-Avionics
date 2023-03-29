#include "highvoltage.h"

void HV_init(void){
    
}

void HV_periodic(void){
    uint16_t now;
    getMillis(&now);
    
    uint16_t HVOnDuration = (((uint16_t)params[PARAM_HV_ON_DURATION_H]) << 8) | params[PARAM_HV_ON_DURATION_L];
    
    //Update state
    if(HVState){
        if((now - HVOnTime) >= HVOnDuration){
            //Turn off
            HVState = FALSE;
            HVLockout = TRUE;
            HVOffTime = now;
            printf("Turning off HV after timeout.\n");
        }
    }
    
    //TODO: write pin state
    
    //Update lockout
    if(HVLockout){
        //Force state false
        //Force button light off
        uint16_t HVLockoutDuration = (((uint16_t)params[PARAM_HV_LOCKOUT_DURATION_H]) << 8) | params[PARAM_HV_LOCKOUT_DURATION_L];
        if(now - HVOffTime >= HVLockoutDuration){
            HVLockout = FALSE;
            printf("HV lockout expired.\n");
        }
    }
}

void HV_requestOn(void){
    if(HVLockout){
        printf("HV request rejected due to lockout.\n");
        return;
    }
    if(HVState){
        printf("HV already on.\n");
        return;
    }
    getMillis(&HVOnTime);
    printf("Turning HV on by request.\n");
    HVState = TRUE;
}