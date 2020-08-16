/*******************************************************************************
 *
 *                  Matriz de LEDs 8x8: Mostrar mensaje estatico
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Mostrar una mensaje estatica en nuestra matriz de LEDs 8x8
 *                  las letras se iran mostrando una a una.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      27/06/2017      Creación del ejemplo
 ******************************************************************************/
#include <xc.h>
#include <stdbool.h>
#include "FUSES_Config.h" //Only here

#define _XTAL_FREQ  16000000

unsigned char letra=0, fila[8];
unsigned int TMR0_Count=0;

void MCU_Init(void);
void TMR0_Init(void);

void interrupt high_priority ISR(void){
    if(INTCONbits.TMR0IF){
        ++TMR0_Count;
        if (TMR0_Count >= 500){
            TMR0_Count = 0;
            switch(letra){ 
                case 0: //M
                    fila[0] = 255;
                    fila[1] = 255;
                    fila[2] = 96;
                    fila[3] = 48;
                    fila[4] = 48; 
                    fila[5] = 96;
                    fila[6] = 255;
                    fila[7] = 255;
                    letra++;
                    break;
                case 1: //R 
                    fila[0]=255;
                    fila[1]=255;
                    fila[2]=216;
                    fila[3]=220;
                    fila[4]=222;
                    fila[5]=219;
                    fila[6]=249;
                    fila[7]=112;
                    letra++;
                    break;
                case 2: //C
                    fila[0]=126;
                    fila[1]=255;
                    fila[2]=195;
                    fila[3]=195;
                    fila[4]=195;
                    fila[5]=195;
                    fila[6]=231;
                    fila[7]=102;
                    letra++;
                    break;
                case 3: //H
                    fila[0]=255;
                    fila[1]=255;
                    fila[2]=24;
                    fila[3]=24;
                    fila[4]=24;
                    fila[5]=24;
                    fila[6]=255;
                    fila[7]=255;
                    letra++;
                    break;
                case 4: //U
                    fila[0]=254;
                    fila[1]=255;
                    fila[2]=3;
                    fila[3]=3;
                    fila[4]=3;
                    fila[5]=3;
                    fila[6]=255;
                    fila[7]=254;
                    letra++;
                    break;
                case 5: //N
                    fila[0]=255;
                    fila[1]=255;
                    fila[2]=112;
                    fila[3]=56;
                    fila[4]=28;
                    fila[5]=14;
                    fila[6]=255;
                    fila[7]=255;
                    letra++;
                    break;
                case 6: //C
                    fila[0]=126;
                    fila[1]=255;
                    fila[2]=195;
                    fila[3]=195;
                    fila[4]=195;
                    fila[5]=195;
                    fila[6]=231;
                    fila[7]=102;
                    letra++;
                    break;
                case 7: //U
                    fila[0]=254;
                    fila[1]=255;
                    fila[2]=3;
                    fila[3]=3;
                    fila[4]=3;
                    fila[5]=3;
                    fila[6]=255;
                    fila[7]=254;
                    letra++;
                    break;
                case 8: //E
                    fila[0]=255;
                    fila[1]=255;
                    fila[2]=219;
                    fila[3]=219;
                    fila[4]=219;
                    fila[5]=219;
                    fila[6]=195;
                    fila[7]=195;
                    letra++;
                    break;
                case 9: //E
                    fila[0]=255;
                    fila[1]=255;
                    fila[2]=219;
                    fila[3]=219;
                    fila[4]=219;
                    fila[5]=219;
                    fila[6]=195;
                    fila[7]=195;
                    letra = 0;
                    break;
            }
        }
        TMR0H = 0xF8;
        TMR0L = 0x30;
        INTCONbits.TMR0IF = 0;
    }
}

void main(void) {
    MCU_Init(); //Inicializamos sistema
    while(true){
        PORTC = 0b00000001;
        PORTB = fila[0];
        __delay_ms(2);
        PORTC = 0b00000010;
        PORTB = fila[1];
        __delay_ms(2);
        PORTC = 0b00000100;
        PORTB = fila[2];
        __delay_ms(2);
        PORTC = 0b00001000;
        PORTB = fila[3];
        __delay_ms(2);
        PORTC = 0b00010000;
        PORTB = fila[4];
        __delay_ms(2);
        PORTC = 0b00100000;
        PORTB = fila[5];
        __delay_ms(2);
        PORTC = 0b01000000;
        PORTB = fila[6];
        __delay_ms(2);
        PORTC = 0b10000000;
        PORTB = fila[7];
        __delay_ms(2);
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