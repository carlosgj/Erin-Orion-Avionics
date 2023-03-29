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
            switch(currentMessage[cursor++]){
                case 's':
                    //Set
                    if(currentMessage[cursor++] != ' '){
                        badMessage = TRUE;
                        break;
                    }
                    break;
                    
                case 'h':
                    printf("Interactive control:\n");
                    printf("s <ch> <val> - Set DAC channel to value\n");
                    printf("q <ch> - Query ADC for channel\n");
                    printf("p <ch> <0|1> - Stop/start test pattern on channel\n");
                    printf("e <0|1> - Disable/enable outputs\n");
                    printf("r <ch> - Query readback (ext. ADC) value\n");
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
