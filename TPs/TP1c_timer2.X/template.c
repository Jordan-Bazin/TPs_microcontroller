#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC


void delai(void) {
    for(int i = 0; i < 125;i++) {
        while(!(PIR1 & 0x02)) {
        
        }
        PIR1 &= ~0x02;
    }
} 

void main(void) {
    /* Code d'initialisation */
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    
    PR2 = 124;
    T2CON |= 0x04;
    T2CON |= 0x02;
    T2CON &= ~0x78;
    
    LATD = 0;
    LATB = 0;
    
    while(1){
        /* Code a executer dans une boucle infinie */    
        for(int i = 0;i < 8;i++)
        {
            LATDbits.LATD0 = 1;
            delai();
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 1;
            delai();
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 1;
            delai();
            LATDbits.LATD2 = 0;
            LATDbits.LATD3 = 1;
            delai();
            LATDbits.LATD3 = 0;
            LATBbits.LATB0 = 1;
            delai();
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 1;
            delai();
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 1;
            delai();
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
            delai();
            LATBbits.LATB3 = 0;
        }
    }
}
