#include <xc.h>
#include "UART.h"

void debug_UART_init(void){
    FIFOInit(&DbgUARTRxBuf);
    
    //Setup UART pins
    ANSELBbits.ANSELB0 = FALSE;
    TRISBbits.TRISB0 = INPUT;
    U1RXPPS = 0b001000;
    
    ANSELBbits.ANSELB3 = FALSE;
    TRISBbits.TRISB3 = OUTPUT;
    RB3PPS = 0x20;
    
    //Setup BRG
    U1CON0bits.BRGS = TRUE;
    U1BRGH = 0;
    U1BRGL = 138;
    
    //Setup transmitter
    U1CON0bits.TXEN = TRUE;

    //Setup receiver
    U1CON0bits.RXEN = TRUE;
    
    //Turn on port
    U1CON1bits.ON = TRUE;
    
    PIE4bits.U1RXIE = TRUE;
}

void putch(unsigned char theByte){
    U1TXB = theByte;
    while(!U1ERRIRbits.TXMTIF){
    }
}

void __interrupt(irq(U1RX),high_priority) DbgUARTRxISR(void){
    FIFOPush(&DbgUARTRxBuf, U1RXB);
}
