#include "highvoltage.h"

void HV_init(void){
    TRISDbits.TRISD4 = OUTPUT;
    LATDbits.LATD4 = FALSE;
}

void HV_periodic(void){
    uint16_t now;
    getMillis(&now);
    
    uint16_t HVOnDuration = get16BitParam(PARAM_HV_ON_DURATION_L);
    
    //Update state
    if(HVState){
        if((now - HVOnTime) >= HVOnDuration){
            //Turn off
            HVState = FALSE;
            HVLockout = TRUE;
            HVOffTime = now;
            printf("%u Turning off HV after timeout.\n", now);
        }
    }
    
    //Update lockout
    if(HVLockout){
        //Force state false
        //Force button light off
        uint16_t HVLockoutDuration = get16BitParam(PARAM_HV_LOCKOUT_DURATION_L);
        if(now - HVOffTime >= HVLockoutDuration){
            HVLockout = FALSE;
            printf("%u HV lockout expired.\n", now);
        }
    }
    
    //Implement state
    if(HVState){
        LATDbits.LATD4 = TRUE;
    }
    else{
        LATDbits.LATD4 = FALSE;
    }
}

void HV_requestOn(void){
    uint16_t now;
    getMillis(&now);
    if(HVLockout){
        printf("%u HV request rejected due to lockout.\n", now);
        return;
    }
    if(HVState){
        printf("%u HV already on.\n", now);
        return;
    }
    HVOnTime = now;
    printf("%u Turning HV on by request.\n", HVOnTime);
    HVState = TRUE;
}