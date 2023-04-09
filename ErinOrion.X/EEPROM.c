#include "EEPROM.h"

uint8_t EEPROM_read(uint16_t addr){
    NVMADRU = 0x38;
    NVMADRH = (uint8_t)(addr >> 8);
    NVMADRL = (uint8_t)(addr & 0xff);
    NVMCON1bits.CMD = 0b000;
    NVMCON0bits.GO = TRUE;
    while(NVMCON0bits.GO){
    }
    //printf("EEP: 0x38%0.4X is 0x%0.2X\n", addr, NVMDATL);
    return NVMDATL;
}

void EEPROM_write(uint16_t addr, uint8_t data){
    printf("Writing 0x%0.2X to 0x38%0.4X...\n", data, addr);
    NVMADRU = 0x38;
    NVMADRH = (uint8_t)(addr >> 8);
    NVMADRL = (uint8_t)(addr & 0xff);
    NVMDATL = data;
    NVMCON1bits.CMD = 0b011;
    
    //Critical sequence
    INTDIS;
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = TRUE;
    while(NVMCON0bits.GO){
    }
    INTEN;
    //printf("%u\n", NVMCON1bits.WRERR);
    NVMCON1bits.CMD = 0b000;
}