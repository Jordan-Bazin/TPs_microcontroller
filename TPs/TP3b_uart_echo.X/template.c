#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC 

void envoyerChaine(char *chaine) {
    for(int i = 0 ;i < sizeof(chaine)*8; i++){
        TX1REG = chaine[i];
    }
    
}



void main(void) {

    RC6PPS = 0x14;
    RXPPS = 0x17;
    
    TRISCbits.TRISC6 = 0;
    ANSELCbits.ANSC6 = 0;
    
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSC7 = 0;
    
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 0;
    BAUD1CONbits.BRG16 = 1;
    
    SP1BRGL = 51;
    SP1BRGH = 0;
    
    RC1STAbits.SPEN = 1;
    TX1STAbits.TXEN = 1;
    RC1STAbits.CREN = 1;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    
    char *tab = "Hello, World !\n\r";
    
    envoyerChaine(tab);
    
    
    
    while(1){
        
    }
}
