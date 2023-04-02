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
                        i = currentMessage[cursor++]-48;
                        if(currentMessage[cursor++] != ' '){
                            badMessage = TRUE;
                            break;
                        }
                        j = (uint8_t)atoi(&(currentMessage[cursor++]));
                        //i is index, j is value
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
                    
                case 't':
                    //lamp test
                    break;
                    
                case 'x':
                    RESET();
                    break; //lol
                    
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
                    printf("\tt <0|1> - lamp test off/on\n");
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
