#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

int time_ms = 0;

void chen() {
    if(LATD & 0x01) {
        LATB = 0;
        LATD = 0x02;
    }else if(LATD & 0x02) {
        LATD = 0;
        LATD = 0x04;
    }else if(LATD & 0x04) {
        LATD = 0;
        LATD = 0x08;
    }else if(LATD & 0x08) {
        LATD = 0;
        LATB = 0x01;
    }else if(LATB & 0x01) {
        LATB = 0;
        LATB = 0x02;
    }else if(LATB & 0x02) {
        LATB = 0;
        LATB = 0x04;
    }else if(LATB & 0x04) {
        LATB = 0;
        LATB = 0x08;
    }else{
        LATB = 0;
        LATD = 0x01;
    }
}

void __interrupt() toto(void) {
    PIR1bits.TMR2IF = 0;
 
    if(time_ms == 124){
        chen();
        time_ms = 0;
    }
    time_ms++;
}

void main(void) {
    /* Code d'initialisation */
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    
    PR2 = 124;
    T2CON |= 0x04;
    T2CON |= 0x02;
    T2CON &= ~0x78;
    
    LATD = 0x01;
    LATB = 0;
    
    INTCON |= 0x80; // mise à 1 de GIE
    INTCON |= 0x40; // mise à 1 de PEIE
    PIE1 |= 0x02; // mise à 1 de TMR2IE
    
    while(1){}
}
