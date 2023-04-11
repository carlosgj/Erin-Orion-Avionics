#include "thrusters.h"

void thrusters_init(void){
    TRISBbits.TRISB0 = OUTPUT;
    TRISBbits.TRISB1 = OUTPUT;
    TRISDbits.TRISD6 = OUTPUT;
    TRISDbits.TRISD7 = OUTPUT;
    
    LATBbits.LATB0 = FALSE;
    LATBbits.LATB1 = FALSE;
    LATDbits.LATD6 = FALSE;
    LATDbits.LATD7 = FALSE;
}

void thrusters_periodic(void){
    static uint16_t stateCounter = 0;
    uint16_t now;
    getMillis(&now);
    //Iterate state machine
    switch(maneuverState){
        case MAN_STATE_OFF:
            if(maneuver){
                if((PRNGLatestFull > (uint16_t)MANEUVER_OFFSET) && (PRNGLatestFull < (uint16_t)(MANEUVER_OFFSET + params[PARAM_MAN_PROB])) ){
                    printf("%u Starting maneuver\n", now);
                    //printf("%u, %u, %u\n", PRNGLatestFull, (uint16_t)MANEUVER_OFFSET, (uint16_t)(MANEUVER_OFFSET + params[PARAM_MAN_PROB]));
                    maneuverState = MAN_STATE_RAMPUP;
                    LEDBrightness[MAIN_THRUSTER_LED_INDEX_1] = 0; //Just to be sure
                    LEDBrightness[MAIN_THRUSTER_LED_INDEX_2] = 0;
                    LEDBrightness[MAIN_THRUSTER_LED_INDEX_3] = 0;
                    stateCounter = 0;
                }
            }
            break;
            
        case MAN_STATE_RAMPUP:
            LEDBrightness[MAIN_THRUSTER_LED_INDEX_1] += params[PARAM_THRUST_RAMPUP_INC];
            LEDBrightness[MAIN_THRUSTER_LED_INDEX_2] += params[PARAM_THRUST_RAMPUP_INC];
            LEDBrightness[MAIN_THRUSTER_LED_INDEX_3] += params[PARAM_THRUST_RAMPUP_INC];
            stateCounter++;
            if(stateCounter == params[PARAM_THRUST_RAMPUP_TIME]){
                printf("%u Thruster rampup done.\n", now);
                maneuverState = MAN_STATE_ON;
                stateCounter = 0;
            }
            break;
            
        case MAN_STATE_ON:
            stateCounter++;
            if(stateCounter > params[PARAM_MAN_MIN_TIME]){
                //Randomize
                if((PRNGLatestSmall > MANEUVER_OFFSET) && (PRNGLatestSmall < (MANEUVER_OFFSET + params[PARAM_MAN_OFF_PROB]))){
                    //Stop maneuver
                    printf("%u Stopping maneuver\n", now);
                    maneuverState = MAN_STATE_RAMPDOWN;
                    stateCounter = 0;
                }
            }
            break;
            
        case MAN_STATE_RAMPDOWN:
            if(LEDBrightness[MAIN_THRUSTER_LED_INDEX_1] < params[PARAM_THRUST_RAMPDWN_INC]){
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_1] = 0;
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_2] = 0;
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_3] = 0;
            }
            else{
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_1] -= params[PARAM_THRUST_RAMPDWN_INC];
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_2] -= params[PARAM_THRUST_RAMPDWN_INC];
                LEDBrightness[MAIN_THRUSTER_LED_INDEX_3] -= params[PARAM_THRUST_RAMPDWN_INC];
            }
            
            stateCounter++;
            if(stateCounter == params[PARAM_THRUST_RAMPDWN_TIME]){
                printf("%u Thruster rampdown done.\n", now);
                maneuverState = MAN_STATE_LOCKOUT;
                stateCounter = 0;
            }
            break;
            
        case MAN_STATE_LOCKOUT:
            stateCounter++;
            if(stateCounter > get16BitParam(PARAM_MAN_LOCKOUT_L)){
                printf("%u Maneuver lockout expired.\n", now);
                maneuverState = MAN_STATE_OFF;
            }
            break;
            
        default:
            break;
    }
    
    //RCS thrusters
    uint8_t onProb, offProb;
    //In "idle", RCS firings are rare and short
    if(maneuverState == MAN_STATE_OFF || maneuverState == MAN_STATE_LOCKOUT){
        onProb = params[PARAM_RCS_IDLE_ON_PRB];
        offProb = params[PARAM_RCS_IDLE_OFF_PRB];
    }
    else{
        onProb = params[PARAM_RCS_MAN_ON_PRB];
        offProb = params[PARAM_RCS_MAN_OFF_PRB];
    }
    
    uint8_t rcs;
    
    if(maneuver){    
        for(rcs=0; rcs<4; rcs++){
            uint8_t offset = rcs * 64;
            if((rcsState >> rcs) & 1){
                
                //If this RCS thruster is on, see if we need to turn it off
                if( (PRNGLatestSmall > offset) && (PRNGLatestSmall < (offset + offProb))){
                    //Turn on
                    //printf("Turning off RCS %d\n", rcs);
                    rcsState &= ~(1<<rcs);
                    //printf("RCS: 0x%x\n", rcsState);
                }
            }
            else{
                //If this RCS thruster is off, see if we need to turn it on
                if( (PRNGLatestSmall > offset) && (PRNGLatestSmall < (offset + onProb))){
                    //Turn off
                    //printf("Turning on RCS %d\n", rcs);
                    rcsState |= (1<<rcs);
                    //printf("RCS: 0x%x\n", rcsState);
                }
            }


        }
    }
    else{
        rcsState = 0;
    }
    
    //Implement RCS state
    for(rcs=0; rcs<4; rcs++){
        if((rcsState >> rcs) & 1){
            switch(rcs){
                case 0:
                    LATBbits.LATB0 = TRUE;
                    break;
                case 1:
                    LATBbits.LATB1 = TRUE;
                    break;
                case 2:
                    LATDbits.LATD6 = TRUE;
                    break;
                case 3:
                    LATDbits.LATD7 = TRUE;
                    break;
            }
        }
        else{
            switch(rcs){
                case 0:
                    LATBbits.LATB0 = FALSE;
                    break;
                case 1:
                    LATBbits.LATB1 = FALSE;
                    break;
                case 2:
                    LATDbits.LATD6 = FALSE;
                    break;
                case 3:
                    LATDbits.LATD7 = FALSE;
                    break;
            }
        }
    }
    
}