/*******************************************************************************
 *
 *                  LED intermitente mediante interrupción
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Atendemos la interrupcion del TMR0 cada milisegundo, y 
 *                  realizamos un conteo, al sobrepasar 1000 cambiamos el estado 
 *                  del LED, por lo tanto el LED cambia su estado cada 1 segundo
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.01      28/06/2017      Creación del ejemplo
 ******************************************************************************/
#include <pic18f25k22.h>
#include <xc.h>
#include "FUSES_Config.h"

#define _XTAL_FREQ  16000000

#define ledStatus   PORTCbits.RC7

unsigned int Count = 0;

void MCU_Init(void);
void TMR0_Init(void);

void interrupt high_priority ISR(void){
    if(INTCONbits.TMR0IF){
        ++Count;
        if (Count >= 1000){
            ledStatus ^= 1; //Blink LED
            Count = 0;
        }
        TMR0H = 0xF8;
        TMR0L = 0x30;
        INTCONbits.TMR0IF = 0;
        return;
    }
}

void main(void) {
    MCU_Init();
    while(1){
        
    }
}

void MCU_Init(void){
    //Puertos digitales
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    //Configura oscilador interno a 16MHz
    OSCCONbits.IRCF=0b111; //El ciclo de instruccion es de 0.25 us
    //Puertos como salida
    TRISB = 0x00;
    TRISC = 0x00;
    //Limpiamos puertos
    PORTB = 0x00;
    PORTC = 0x00;
    
    TMR0_Init();
}

void TMR0_Init(void){
    //Configuración del TMR0 = 1mS
    T0CONbits.TMR0ON = 1; //TMR0 On
    T0CONbits.T08BIT = 0; //16 bits
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b000; // Prescaler = 2
    TMR0H = 0xF8;
    TMR0L = 0x30;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCON2bits.TMR0IP = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
}