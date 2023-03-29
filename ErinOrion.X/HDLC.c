#include <xc.h>
#include "HDLC.h"

void HDLCInit(void){

}

void sendBuf(uint8_t *buf, unsigned int count){
    unsigned int i = 0;
    LATEbits.LATE2 = TRUE;
    //Write start byte
    UART_write(HDLC_START);
    
    //Perform byte-stuffing & write message
    for(i=0; i<count; i++){
        if( IS_CONTROL(buf[i]) ){
            UART_write(HDLC_ESCAPE);
            UART_write((unsigned char)(buf[i] ^ 0b00100000));
        }
        else{
            UART_write(buf[i]);
        }
    }

    UART_write(HDLC_STOP);
    LATEbits.LATE2 = FALSE;
}

void implementRx(FIFO *RxQueue){
    //Check if there are unprocessed bytes in rx queue
    unsigned char toRead;
    static unsigned char isEscape = FALSE;
    static unsigned char isInMessage = FALSE;
    //__delay_ms(5);
    for(toRead = FIFOGetUsed(RxQueue); toRead > 0; toRead--){
        unsigned char newByte;
        FIFOPop(RxQueue, &newByte);
        if(newByte == HDLC_ESCAPE){
            isEscape = TRUE;
            continue;
        }

        //Not an escape byte
        if(isEscape){
            if((newByte & 0b00100000) != 0){
                //We got an escape byte and then a byte without bit 5 clear
                //Abort reception
                isInMessage = FALSE;
                framePtr = 0;
                //commErrors.byteStuff++;
                printf("Bytestuff error!\n");
                continue;
            }
            else{
                frameBuf[framePtr++] = (unsigned char)(newByte ^ 0b00100000);
            }
            isEscape = FALSE;
        }
        else{
            frameBuf[framePtr++] = newByte;
        }
        
        
        if(newByte == HDLC_STOP){
            if(isInMessage){
                //End of message.
                isInMessage = FALSE;
                validateFrame(framePtr);
                framePtr = 0;
                continue;
            }
            else{
                //We got a stop byte when a message wasn't in progress
                //commErrors.framing++;
                printf("Stop byte during idle!\n");
            }
        }
        
        if(newByte == HDLC_START){
            if(isInMessage){
                //We got a start byte while a message was in progress
                //commErrors.framing++;
                printf("Start byte during message!\n");
                framePtr = 0;
            }
            else{
                isInMessage = TRUE;
            }
        }
        
        if(framePtr == FRAMEBUF_SIZE){
            //Buffer overrun
            //commErrors.oversizeFrame++;
            printf("Oversize frame!\n");
            framePtr = 0;
            isInMessage = FALSE;
        }
    }
}