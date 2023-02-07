#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000


void main(void) {
    /* Code d'initialisation */
    ANSELAbits.ANSA0 = 0; // RA5 est une entree numerique
    
    TRISA0 |= 0xFF; 
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    
    PR2 = 124;
    T2CON |= 0x04;
    T2CON |= 0x02;
    T2CON &= ~0x78;
    
    LATD = 0;
    LATB = 0;
    
    // setup de l'adc
    ADCON1bits.ADCS = 0;
    ADCON1bits.ADFM = 0;
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
    
 
    int i = 0;
    int ADCH = 0;
    int ADCL = 0;
    
    while(1){
        if(ADCON0bits.ADGO == 0)
        {
            ADCON0bits.ADGO = 1;
            int ADCH = ADRESH;
            int ADCL = ADRESL & 0xC0; // lecture des 2 bits de poids fort
            int res =  (ADCL >> 6) + (ADCH << 2); // on créer un entier sur 10 bits 
            
            if(res <= 1023 && res > 895){
                LATB = 0;
                LATD = 0;
                LATBbits.LATB3 = 1;
            }
            else if(res <= 895 && res > 767){
                LATB = 0;
                LATD = 0;
                LATBbits.LATB2 = 1;
            }
            else if(res <= 767 && res > 639){
                LATB = 0;
                LATD = 0;
                LATBbits.LATB1 = 1;
            }
            else if(res <= 639 && res > 511){
                LATB = 0;
                LATD = 0;
                LATBbits.LATB0 = 1;
            }
            else if(res <= 511 && res > 383){
                LATB = 0;
                LATD = 0;
                LATDbits.LATD3 = 1;
            }
            else if(res <= 383 && res > 255){
                LATB = 0;
                LATD = 0;
                LATDbits.LATD2 = 1;
            }
            else if(res <= 255 && res > 127){
                LATB = 0;
                LATD = 0;
                LATDbits.LATD1 = 1;
            }
            else if(res < 127){
                LATB = 0;
                LATD = 0;
                LATDbits.LATD0 = 1;
            }
        }
    }
}
