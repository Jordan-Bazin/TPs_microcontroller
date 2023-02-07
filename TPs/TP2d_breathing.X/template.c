#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000

int time_ms = 0;
int j = 0;

void fsm_pwm(int i){
    switch (i) {
        case 0:
            PWM4DCH = 15;
            PWM4DCL = 64;
            break;
        case 1:
            PWM4DCH = 31;
            PWM4DCL = 64;
            break;
        case 2:
            PWM4DCH = 47;
            PWM4DCL = 64;
            break;
        case 3:
            PWM4DCH = 63;
            PWM4DCL = 64;
            break;
        case 4:
            PWM4DCH = 79;
            PWM4DCL = 64;
            break;
        case 5:
            PWM4DCH = 95;
            PWM4DCL = 64;
            break;
        case 6:
            PWM4DCH = 111;
            PWM4DCL = 64;
            break;
        case 7:
            PWM4DCH = 127;
            PWM4DCL = 64;
            break;
        case 8:
            PWM4DCH = 0;
            PWM4DCL = 0;
            break;
    }
}

void __interrupt() toto(void) {
    PIR1bits.TMR2IF = 0;
 
    if(time_ms == 124){
        time_ms = 0;
        if(j > 7) {
            switch (j) {
            case 8:
                fsm_pwm(6);
                j++;
                break;
            case 9:
                fsm_pwm(5);
                j++;
                break;
            case 10:
                fsm_pwm(4);
                j++;
                break;
            case 11:
                fsm_pwm(3);
                j++;
                break;
            case 12:
                fsm_pwm(2);
                j++;
                break;
            case 13:
                fsm_pwm(1);
                j++;
                break;
            case 14:
                fsm_pwm(0);
                j++;
                break;
            case 15:
                fsm_pwm(8);
                j = 0;
                break;
        }
        }
        switch (j) {
            case 0:
                fsm_pwm(j);
                j++;
                break;
            case 1:
                fsm_pwm(j);
                j++;
                break;
            case 2:
                fsm_pwm(j);
                j++;
                break;
            case 3:
                fsm_pwm(j);
                j++;
                break;
            case 4:
                fsm_pwm(j);
                j++;
                break;
            case 5:
                fsm_pwm(j);
                j++;
                break;
            case 6:
                fsm_pwm(j);
                j++;
                break;
            case 7:
                fsm_pwm(j);
                j++;
                break;
        }
    }
    time_ms++;
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
    
    INTCON |= 0x80; // mise à 1 de GIE
    INTCON |= 0x40; // mise à 1 de PEIE
    PIE1 |= 0x02; // mise à 1 de TMR2IE
    
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
    
    while(1){}
}
