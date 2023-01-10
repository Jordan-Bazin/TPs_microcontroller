#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC


void delai_approx(void) {
    for(int i = 0;i < 30000; i++){}
    for(int i = 0;i < 30000; i++){}
    for(int i = 0;i < 30000; i++){}
} 

void main(void) {
    /* Code d'initialisation */
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
        
    while(1){
        /* Code a executer dans une boucle infinie */
        LATB = 0x00;  // Eteint les leds de PORTB
        LATD = 0xFF; // Allume les leds de PORTD
        delai_approx();
        LATB = 0xFF; // Allume les leds de PORTB
        LATD = 0x00; // // Eteint les leds de PORTD
        delai_approx();
    }
}
