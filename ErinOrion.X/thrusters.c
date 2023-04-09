#include "thrusters.h"

void thrusters_init(void){
    
}

void thrusters_periodic(void){
    static uint8_t stateCounter = 0;
    
    //Iterate state machine
    switch(maneuverState){
        case MAN_STATE_OFF:
            if(maneuver){
                printf("Starting maneuver\n");
                maneuverState = MAN_STATE_RAMPUP;
                LEDBrightness[MAIN_THRUSTER_LED_INDEX] = 0; //Just to be sure
                stateCounter = 0;
            }
            break;
            
        case MAN_STATE_RAMPUP:
            LEDBrightness[MAIN_THRUSTER_LED_INDEX] += params[PARAM_THRUST_RAMPUP_INC];
            stateCounter++;
            if(stateCounter == params[PARAM_THRUST_RAMPUP_TIME]){
                printf("Thruster rampup done.\n");
                maneuverState = MAN_STATE_ON;
            }
            break;
            
        case MAN_STATE_ON:
            if(!maneuver){
                printf("Finishing maneuver\n");
                maneuverState = MAN_STATE_RAMPDOWN;
            }
            break;
            
        case MAN_STATE_RAMPDOWN:
            if(LEDBrightness[MAIN_THRUSTER_LED_INDEX] < params[PARAM_THRUST_RAMPDWN_INC]){
                LEDBrightness[MAIN_THRUSTER_LED_INDEX] = 0;
            }
            else{
                LEDBrightness[MAIN_THRUSTER_LED_INDEX] -= params[PARAM_THRUST_RAMPDWN_INC];
            }
            
            stateCounter++;
            if(stateCounter == params[PARAM_THRUST_RAMPDWN_TIME]){
                printf("Thruster rampdown done.\n");
                maneuverState = MAN_STATE_OFF;
            }
            break;
            
        default:
            break;
    }
    
    //RCS thrusters
    uint8_t onProb, offProb;
    //In "idle", RCS firings are rare and short
    if(maneuverState == MAN_STATE_OFF){
        onProb = params[PARAM_RCS_IDLE_ON_PRB];
        offProb = params[PARAM_RCS_IDLE_OFF_PRB];
    }
    else{
        onProb = params[PARAM_RCS_MAN_ON_PRB];
        offProb = params[PARAM_RCS_MAN_OFF_PRB];
    }
    
    uint8_t rcs;
    for(rcs=0; rcs<4; rcs++){
        uint8_t offset = rcs * 64;
        if((rcsState >> rcs) & 1){
            //If this RCS thruster is on, see if we need to turn it off
            if( (PRNGLatestSmall > offset) && (PRNGLatestSmall < (offset + offProb))){
                //Turn on
                printf("Turning off RCS %d\n", rcs);
                rcsState &= ~(1<<rcs);
                printf("RCS: 0x%x\n", rcsState);
            }
        }
        else{
            //If this RCS thruster is off, see if we need to turn it on
            if( (PRNGLatestSmall > offset) && (PRNGLatestSmall < (offset + onProb))){
                //Turn off
                printf("Turning on RCS %d\n", rcs);
                rcsState |= (1<<rcs);
                printf("RCS: 0x%x\n", rcsState);
            }
        }
        
        
    }
}

void thrusters_setState(uint8_t state){
    
}