/*******************************************************************************
 *
 *                  Matriz de LEDs 8x8: Mostrar carácter estatico
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42 & MPLAB X IDE v3.61
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Mostrar una imagen estatica en nuestra matriz de LEDs 8x8
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      24/05/2017      Creación del ejemplo
 ******************************************************************************/
#include <xc.h>
#include <stdbool.h>
#include "FUSES_Config.h" //Only here

#define _XTAL_FREQ  16000000

unsigned char x;
//Caracter PacMan
const char ROW[8] = {0b00111100, 
                     0b01000010, 
                     0b10000001, 
                     0b10100001,
                     0b10001001, 
                     0b10010101, 
                     0b10100101, 
                     0b01000010};
//Para hacer el barrido de las columnas
const char COL[8] = {0b00000001,
                     0b00000010,
                     0b00000100,
                     0b00001000,
                     0b00010000,
                     0b00100000,
                     0b01000000,
                     0b10000000};

void MCU_Init(void);
void MCU_Delayms(unsigned int t);

void main(void) {
    MCU_Init(); //Inicializamos sistema
    while(true){
        PORTB = ROW[x]; //Mostramos 
        PORTC = COL[x]; //Hacemos barrido
        MCU_Delayms(1);
        x++;//Incrementamos ROW y COL
        if(x>8) x=0;//No dejamos que pase de 8
    }
    return;
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
}

void MCU_Delayms(unsigned int t){
    unsigned int acc;
    for(acc=0; acc<t; acc++){
        __delay_ms(1);
    }
}