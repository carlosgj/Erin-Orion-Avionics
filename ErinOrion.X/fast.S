#include <pic18f45q43.inc>
;#include "shared.h"
; When assembly code is placed in a psect, it can be manipulated as a
; whole by the linker and placed in memory.  
;
; In this example, barfunc is the program section (psect) name, 'local' means
; that the section will not be combined with other sections even if they have
; the same name.  class=CODE means the barfunc must go in the CODE container.
; PIC18's should have a delta (addressible unit size) of 1 (default) since they
; are byte addressible.  PIC10/12/16's have a delta of 2 since they are word
; addressible.  PIC18's should have a reloc (alignment) flag of 2 for any
; psect which contains executable code.  PIC10/12/16's can use the default
; reloc value of 1.  Use one of the psects below for the device you use:

;psect   barfunc,local,class=CODE,delta=2 ; PIC10/12/16
psect   barfunc,local,class=CODE,reloc=2 ; PIC18

#define NP_PIN LATC6
    
global _NeoPixel_sendData

_NeoPixel_sendData:
    ;diable interrupts
    bcf GIE
    
    lfsr 0, 604h
    
    byteStart1:
    ;first bit (bit 7) starts here
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 7
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 7; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 6
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 6
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 6; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 5
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 5
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 5; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 4
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 4
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 4; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 3
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 3
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 3; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 2
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 2
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 2; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;Bit 1
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 1
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    nop
    btfsc INDF0, 1; turn off if this is a 1
    bcf NP_PIN
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    ;bit 0
    bsf NP_PIN ;Turn on
    nop
    nop
    nop
    btfss INDF0, 0
    bcf NP_PIN; turn off if this is a 0
    nop
    nop
    decfsz FSR0L
    goto lastBCF1
    nop
    goto exit1
    lastBCF1:
    bcf NP_PIN
    nop
    nop
    nop
    goto byteStart1
    
    exit1:
    bcf NP_PIN
    
    ;reenable interrupts
    bsf GIE
    
    return