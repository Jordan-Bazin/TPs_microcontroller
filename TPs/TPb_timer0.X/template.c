#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC


void delai_1s(void) {   
    for(int i = 0; i < 1000;i++) {
        while(!(INTCON & 0x04)) {
        
        }
        INTCON &= ~0x04;
        TMR0 = 6;
    }
    
} 

void main(void) {
    /* Code d'initialisation */
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    OPTION_REG &= ~0x05; // Prescaler = 010 = 8
    OPTION_REG &= ~0x08; // Permet d'assigner la nouvelle valeur pour TMR0
    OPTION_REG &= ~0x20; // TMR0CS mis à 0 pour utiliser Fosc/4
    TMR0 = 6;
    
    while(1){
        /* Code a executer dans une boucle infinie */
        LATB = 0x00;  // Eteint les leds de PORTB
        LATD = 0xFF; // Allume les leds de PORTD
        delai_1s();
        LATB = 0xFF; // Allume les leds de PORTB
        LATD = 0x00; // // Eteint les leds de PORTD
        delai_1s();
    }
}
