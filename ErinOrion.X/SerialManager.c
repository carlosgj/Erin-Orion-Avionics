#include "SerialManager.h"

void dbgSerialPeriodic(void){
    if(FIFOGetUsed(&DbgUARTRxBuf) > 0){
        //printf("%u\n", FIFOGetUsed(&DbgUARTRxBuf));
        uint8_t thisChar;
        FIFOPop(&DbgUARTRxBuf, &thisChar);
        //printf("<%u\n", thisChar);
        currentMessage[currentMessageIdx++] = thisChar;
        if(currentMessageIdx == 19){
            printf("Debug command too long!\n");
            currentMessageIdx = 0;
        }
        if(thisChar == '\n' || thisChar == '\r'){
            //Process message
            currentMessage[currentMessageIdx] = 0;
            
            //printf("<%s\n", currentMessage);
            uint8_t cursor=0;
            uint8_t badMessage = FALSE;
            
            uint8_t i, j;
            uint16_t uint16;
            
            switch(currentMessage[cursor++]){
                case 'p':
                    if(currentMessageIdx == 2){
                        //Single 'p' character
                        //Dump params
                        for(i=0; i<NUM_PARAMS; i++){
                            printf("%u: %u\n", i, params[i]);
                        }
                        break;
                    }
                    else{
                        if(currentMessage[cursor++] != ' '){
                            badMessage = TRUE;
                            break;
                        }
                        
                        //Get index
                        i = (uint8_t)atoi((int8_t *)&(currentMessage[cursor++]));
                        
                        //Advance cursor to the next space
                        while(cursor < currentMessageIdx){
                            if(currentMessage[cursor] == ' '){
                                break;
                            }
                            cursor++;
                        }
                        if(cursor == currentMessageIdx){
                            //No space found
                            badMessage = TRUE;
                            break;
                        }
                        
                        j = (uint8_t)atoi(&(currentMessage[cursor++]));
                        //i is index, j is value
                        if(i >= NUM_PARAMS){
                            printf("Param index out of range!\n");
                            break;
                        }
                        printf("Setting param %u to %u...\n", i, j);
                        write_param(i, j);
                        break;
                    }
                    break;
                    
                case 'l':
                    //Load params
                    switch(currentMessage[cursor++]){
                        case 'e':
                            //load params from EEPROM
                            i = loadParamsFromEEPROM();
                            if(i == PARAM_LOAD_SUCCESS){
                                printf("Params loaded from EEPROM.\n");
                            }
                            else{
                                printf("Error %u loading params from EEPROM!\n", i);
                                loadParamsFromProgram();
                                printf("Params loaded from program memory.\n");
                            }
                            break;
                        case 'p':
                            //load params from program memory
                            loadParamsFromProgram();
                            printf("Params loaded from program memory.\n");
                            break;
                        default:
                            badMessage = TRUE;
                            break;
                    }
                    break;
                    
                case 'b':
                    //burn params to EEPROM
                    burnParamsToEEPROM();
                    
                case 'c':
                    if(currentMessageIdx == 2){
                        //Single 'c' character
                        //Dump PWMs
                        for(i=0; i<24; i++){
                            printf("%u: %u\n", i, LEDBrightness[i]);
                        }
                        break;
                    }
                    
                    
                    if(currentMessage[cursor++] != ' '){
                        badMessage = TRUE;
                        break;
                    }
                    
                    //Get channel
                    i = (uint8_t)atoi(&(currentMessage[cursor++]));
                    if(i > 23){
                        printf("Invalid channel.\n");
                        break;
                    }
                    
                    //Advance cursor to the next space
                    while(cursor < currentMessageIdx){
                        if(currentMessage[cursor] == ' '){
                            break;
                        }
                        cursor++;
                    }
                    if(cursor == currentMessageIdx){
                        //No space found
                        badMessage = TRUE;
                        break;
                    }
                      
                    j = (uint8_t)atoi(&(currentMessage[cursor++]));
                    
                    printf("Setting LED channel %d to %u\n", i, j);
                    LEDBrightness[i] = j;
                    
                    break;
                    
                    
                case 't':
                    //lamp test
                    break;
                    
                case 'x':
                    RESET();
                    break; //lol
                    
                case 'v':
                    printf("Requesting HV on\n");
                    HV_requestOn();
                    break;
                    
                case 'h':
                    printf("Interactive control:\n");
                    printf("\tx - Reset\n");
                    printf("Parameter table commands:\n");
                    printf("\tp - Dump params\n");
                    printf("\tp <ID> <val> - Set param\n");
                    printf("\tle - Load params from EEPROM\n");
                    printf("\tb - burn params to EEPROM\n");
                    printf("\tlp - Load params from program memory\n");
                    printf("LED commands:\n");
                    printf("\tc - Dump current PWM values\n");
                    printf("\tc <ch> <val> - Set PWM channel to value\n");
                    printf("High voltage commands:\n");
                    printf("\tv - Trigger HV\n");
                    break;
                default:
                    badMessage = TRUE;
                    break;
            }
            if(badMessage){
                printf("Invalid command received!\n");
            }
            
            
            
            currentMessageIdx = 0;
        }
    }
}
