#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000


void fsm_pwm(int i){
    switch (i) {
        case 1:
            PWM4DCH = 0;
            PWM4DCL = 0;
            break;
        case 2:
            PWM4DCH = 43;
            PWM4DCL = 64;
            break;
        case 3:
            PWM4DCH = 85;
            PWM4DCL = 64;
            break;
        case 4:
            PWM4DCH = 127;
            PWM4DCL = 64;
    }
}

void init_PPS(void){
    RA0PPS = 0x0F;
}

void main(void) {
    /* Code d'initialisation */
    ANSELAbits.ANSA0 = 0;
    TRISAbits.TRISA5 = 1; // RA5 est une entrée (btn S2)
    ANSELAbits.ANSA5 = 0; // RA5 est une entrée numérique
            
    TRISA0 |= 0xFF;
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    
    PR2 = 124;
    T2CON |= 0x04;
    T2CON |= 0x02;
    T2CON &= ~0x78;
    
    LATD = 0;
    LATB = 0;
    
    ADCON1bits.ADCS = 0;
    ADCON1bits.ADFM = 0;
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
    
    PWM4CON = 0x80;
    // configuration des LEDS pour la PWM
    RD0PPS = 0x0F;
    
   
    while(1){
        if(ADCON0bits.ADGO == 0){
            ADCON0bits.ADGO = 1;
            int ADCH = ADRESH;
            int ADCL = ADRESL & 0xC0; // lecture des 2 bits de poids fort
            int res =  (ADCL >> 6) + (ADCH << 2); // on créer un entier sur 10 bits 
            if(res <= 1023 && res > 768) {
                fsm_pwm(4);
            }
            else if(res <= 768 && res > 513){
                fsm_pwm(3);
            }
            else if(res <= 513 && res > 258){
                fsm_pwm(2);
            }
            else if(res <= 258){
                fsm_pwm(1);
            }
        }
    }
}
