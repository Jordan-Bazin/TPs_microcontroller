#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000


void fsm_pwm(int i){
    switch (i) {
        case 0:
            PWM4DCH = 31;
            PWM4DCL = 64;
            break;
        case 1:
            PWM4DCH = 63;
            PWM4DCL = 64;
            break;
        case 2:
            PWM4DCH = 95;
            PWM4DCL = 64;
            break;
        case 3:
            PWM4DCH = 127;
            PWM4DCL = 64;
    }
}

void init_PPS(void){
    RA0PPS = 0x0F;
}

void main(void) {
    /* Code d'initialisation */
    TRISAbits.TRISA5 = 1; // RA5 est une entrée (btn S2)
    ANSELAbits.ANSA5 = 0; // RA5 est une entrée numérique
            
    TRISD &= 0xF0; // Configuration en sortie de PORTD
    TRISB &= 0xF0; // Configuration en sortie de PORTB
    
    PR2 = 124;
    T2CON |= 0x04;
    T2CON |= 0x02;
    T2CON &= ~0x78;
    
    LATD = 0;
    LATB = 0;
    
    PWM4CON = 0x80;
    // configuration des LEDS pour la PWM
    RD0PPS = 0x0F;
    RD1PPS = 0x0F;
    RD2PPS = 0x0F;
    RD3PPS = 0x0F;
    RB0PPS = 0x0F;
    RB1PPS = 0x0F;
    RB2PPS = 0x0F;
    RB3PPS = 0x0F;
    
    int test = 0;
    int i = 0;
    while(1){
        if(PORTAbits.RA5 == 0){
            test = !test;
            if(test == 0){
                if(i == 0) {
                    fsm_pwm(i);
                    i++;
                }
                else if(i == 1){
                    fsm_pwm(i);
                    i++;
                }
                else if(i == 2){
                    fsm_pwm(i);
                    i++;
                }
                else if(i == 3){
                    fsm_pwm(i);
                    i = 0;
                }
                __delay_ms(150);
                //LATD = 0x0F;
            } else {
                __delay_ms(150);
                //LATD = 0x00;
            }
        }
    }
}
