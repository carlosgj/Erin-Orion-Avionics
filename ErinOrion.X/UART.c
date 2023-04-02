#include <xc.h>
#include "UART.h"

void debug_UART_init(void){
    FIFOInit(&DbgUARTRxBuf);
    
    //Setup UART pins
    ANSELDbits.ANSELD1 = FALSE;
    TRISDbits.TRISD1 = INPUT;
    U2RXPPS = 0b011001;
    
    ANSELDbits.ANSELD0 = FALSE;
    TRISDbits.TRISD0 = OUTPUT;
    RD0PPS = 0x23;
    
    //Setup BRG
    U2CON0bits.BRGS = TRUE;
    U2BRGH = 0;
    U2BRGL = 138;
    
    //Setup transmitter
    U2CON0bits.TXEN = TRUE;

    //Setup receiver
    U2CON0bits.RXEN = TRUE;
    
    //Turn on port
    U2CON1bits.ON = TRUE;
    
    PIE8bits.U2RXIE = TRUE;
}

void putch(unsigned char theByte){
    U2TXB = theByte;
    while(!U2ERRIRbits.TXMTIF){
    }
}

void __interrupt(irq(U2RX),high_priority) DbgUARTRxISR(void){
    FIFOPush(&DbgUARTRxBuf, U2RXB);
}
