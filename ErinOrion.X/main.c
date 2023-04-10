#include "main.h"

void main(void) {
    uint16_t startTime;
    uint16_t currentTime;
    getResetCause();
    init();
    while(TRUE){
        getMillis(&startTime);
        wdtCheckWord = 0;
        periodicTasks();
        if(wdtCheckWord == WDT_CHECK_GOOD){
            CLRWDT();
        }
        getMillis(&currentTime);
        
        if((currentTime - startTime) >= MAIN_LOOP_TIME){
            //Cycle slip!
            status.loopOverruns++;
            continue;
        }
        
        cycleSlack = MAIN_LOOP_TIME - (currentTime - startTime);
        if(cycleSlack < minCycleSlack){
            minCycleSlack = cycleSlack;
        }
        while(TRUE){
            getMillis(&currentTime);
            uint16_t elapsedTime = currentTime - startTime;
            if(elapsedTime >= MAIN_LOOP_TIME){
                break;
            }
        }
    }
}

void init(void){
    INTDIS;
    //Setup oscillator    
    INTCON0bits.IPEN = TRUE;
    INTCON0bits.GIEL = TRUE;
#ifdef LOOPOUT
    TRISAbits.TRISA4 = OUTPUT;
#endif
    INTEN;
    
    //All pins to digital
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    
    //Set up misc indicator LEDs
    TRISCbits.TRISC2 = OUTPUT;
    TRISCbits.TRISC3 = OUTPUT;
    TRISCbits.TRISC5 = OUTPUT;
    LED3LAT = FALSE;
    LED4LAT = FALSE;
    
    memset(status.all, 0, STATUS_LEN); //Initialize system error counters
    
    timerInit();
    //__delay_ms(500);
    
    debug_UART_init();
    __delay_ms(10);
    
    printf("Serial initialized.\n");
    printf("SW ver: %s\n", SW_VER_STR);
    printf("Compiled: %s %s\n", __DATE__, __TIME__);
    printf("Git ver: %s\n", GIT_VERSION);
    printf("Last reset: %d\n", resetCause);
    status.resetCause = resetCause;
    
    uint8_t i;
    for(i=0; i<5; i++){
        buttonHoldTimes[i] = 0;
    }
    
    HV_init();
    printf("High voltage control functions initialized.\n");
    
    uint8_t paramLoadStatus = loadParamsFromEEPROM();
    if(paramLoadStatus == PARAM_LOAD_SUCCESS){
        printf("Params loaded from EEPROM.\n");
    }
    else{
        printf("Error %u loading params from EEPROM!\n", paramLoadStatus);
        loadParamsFromProgram();
        printf("Params loaded from program memory.\n");
    }
    
    
    TLC5947_init();
    printf("TLC5947 initialized.\n");
    
    button_init();
    printf("Buttons initialized.\n");
    
    ADC_init();
    printf("ADC initialized.\n");
    
    PRNG_Init();
    printf("Pseudorandom number generator initialized.\n");
    
    thrusters_init();
    printf("Thrusters initialized.\n");
    
    NeoPixel_init();
    printf("NeoPixel control initialized.\n");
    
    UI_init();
    printf("User interface enabled.\n");
    
    printf("Initialization done.\n");
#if defined(LOOPOUT) || defined(MSOUT)
    TRISAbits.TRISA0 = OUTPUT;
#endif
}

void periodicTasks(void){
    static uint8_t counter;
    LED3LAT = !LED3LAT;
    
    counter++;
    if(counter==0){
        //printf("Cycle slack: %u ms\n", cycleSlack);
        printf("Minimum cycle slack: %u ms / %u ms\n", minCycleSlack, MAIN_LOOP_TIME);
        minCycleSlack = 0xffff;
        
    }    
    
#ifdef LOOPOUT
    //LATAbits.LATA0 = !LATAbits.LATA0;
#endif
    dbgSerialPeriodic();
    updateInputs();
    PRNG_Periodic();
    thrusters_periodic();
    TLC5947_write();
    NeoPixel_sendData();
    HV_periodic();
    UI_periodic();
    
    if(paramScrub() != PARAM_SCRUB_SUCCESS){
        printf("FATAL: Param scrub failure!\n");
        RESET();
    }
    
    //Memory scan increment
    
}

void getResetCause(void){
    //Attempt to figure out what caused reset
    if(!PCON1bits.nMEMV){
        //Memory violation
        resetCause = RS_MEM;
        PCON1bits.nMEMV = TRUE;
        return;
    }
    
    if(PCON0bits.STKOVF){
        //Stack overflow
        resetCause = RS_SO;
        PCON0bits.STKOVF = FALSE;
        return;
    }
    
    if(PCON0bits.STKUNF){
        //Stack underflow
        resetCause = RS_SU;
        PCON0bits.STKUNF = FALSE;
        return;
    }
    
    if(!PCON0bits.nWDTWV){
        //WDT window violation
        resetCause = RS_WIN;
        PCON0bits.nWDTWV = TRUE;
        return;
    }
    
    if(!PCON0bits.nRWDT){
        //WDT reset
        resetCause = RS_WDT;
        PCON0bits.nRWDT = TRUE;
        return;
    }
    
    if(!PCON0bits.nRMCLR){
        //MCLR
        resetCause = RS_MCLR;
        PCON0bits.nRMCLR = TRUE;
        return;
    }
    
    if(!PCON0bits.nPOR){
        //Power-on reset
        resetCause = RS_POR;
        PCON0bits.nPOR = TRUE;
        return;
    }
    
    if(!PCON0bits.nBOR){
        //Brownout
        resetCause = RS_BOR;
        PCON0bits.nBOR = TRUE;
        return;
    }
    
}

void __interrupt(irq(default),high_priority) DefaultISR(unsigned char id){
    status.unhandledIntCount++;
    status.lastUnhandledInt = id;
    //printf("Unhandled interrupt!\n");
}