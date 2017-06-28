/*******************************************************************************
 *
 *                  XC8_009: Matriz de LEDs 8x8: Mostrar abecedario y numeros
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42 & MPLAB X IDE v3.61
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Luces para regalo
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      28/06/2017      Creación del ejemplo
 ******************************************************************************/
#include <xc.h>
#include <stdbool.h>
#include "FUSES_Config.h" //Only here

#define _XTAL_FREQ  16000000

// Define Alphabets A through Z
const unsigned int Alphabets[]={
    0x00, 0x3F, 0x7F, 0xE4, 0xE4, 0x7F, 0x3F, 0x00, //A
    0x00, 0xFF, 0xFF, 0x99, 0x99, 0xFF, 0x66, 0x00, //B
    0x00, 0x3C, 0x7E, 0xC3, 0x81, 0xC3, 0x42, 0x00, //C
    0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0x7E, 0x3C, 0x00, //D
    0x00, 0xFF, 0xFF, 0x99, 0x99, 0x99, 0x81, 0x00, //E
    0x00, 0xFF, 0xFF, 0xC8, 0xC8, 0xC8, 0xC0, 0x00, //F
    0x00, 0x7E, 0xFF, 0x81, 0x85, 0xC7, 0x46, 0x00, //G
    0x00, 0xFF, 0xFF, 0x18, 0x18, 0xFF, 0xFF, 0x00, //H
    0x00, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0x00, //I
    0x00, 0x06, 0xC6, 0xC3, 0xFF, 0xFE, 0xC0, 0x00, //J
    0x00, 0xFF, 0xFF, 0x38, 0x6C, 0xC6, 0x83, 0x00, //K
    0x00, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x00, //L
    0xFF, 0xFF, 0x60, 0x30, 0x60, 0xFF, 0xFF, 0x00, //M
    0xFF, 0xFF, 0x60, 0x30, 0x18, 0xFF, 0xFF, 0x00, //N
    0x00, 0x7E, 0xFF, 0xC3, 0xC3, 0xFF, 0x7E, 0x00, //O
    0x00, 0xFF, 0xFF, 0x88, 0x88, 0xF8, 0x70, 0x00, //P
    0x00, 0x7C, 0xFE, 0x82, 0x86, 0xFF, 0x7D, 0x00, //Q
    0x00, 0xFF, 0xFF, 0xD8, 0xDC, 0xF7, 0x63, 0x00, //R
    0x00, 0x72, 0xFB, 0x99, 0x99, 0xDF, 0x4E, 0x00, //S
    0x00, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0x00, //T
    0x00, 0xFE, 0xFF, 0x03, 0x03, 0xFF, 0xFE, 0x00, //U
    0x00, 0xFC, 0xFE, 0x03, 0x03, 0xFE, 0xFC, 0x00, //V
    0xFF, 0xFF, 0x06, 0x0C, 0x06, 0xFF, 0xFF, 0x00, //W
    0xE7, 0xF7, 0x3C, 0x18, 0x3C, 0xEF, 0xE7, 0x00, //X
    0x00, 0xF0, 0xF8, 0x0F, 0x0F, 0xF8, 0xF0, 0x00, //Y
    0x00, 0xC7, 0xCF, 0xDB, 0xDB, 0xF3, 0xE3, 0x00 // Z
    };

//Define numbers 0 to 9
const unsigned int Numbers[] ={
    0x00, 0x7E, 0xFF, 0xCB, 0xD3, 0xFF, 0x7E, 0x00, //0
    0x00, 0x01, 0x61, 0xFF, 0xFF, 0x01, 0x01, 0x00, //1
    0x00, 0x66, 0xCF, 0xCB, 0xD3, 0xF3, 0x62, 0x00, //2
    0x00, 0x42, 0xC3, 0x99, 0x99, 0xFF, 0x6E, 0x00, //3
    0x00, 0x1C, 0x2C, 0x4C, 0xFF, 0xFF, 0x0C, 0x00, //4
    0x00, 0x72, 0xF3, 0x91, 0x91, 0x9F, 0x0E, 0x00, //5 
    0x00, 0x7E, 0xFF, 0x91, 0x91, 0x9F, 0x4E, 0x00, //6 
    0x00, 0xC0, 0xC0, 0x8F, 0x9F, 0xF0, 0xE0, 0x00, //7
    0x00, 0x6E, 0xFF, 0x91, 0x91, 0xFF, 0x6E, 0x00, //8
    0x00, 0x70, 0xF8, 0x88, 0x88, 0xFF, 0x7F, 0x00  //9
    };

unsigned int count, column, num, repeat;

void MCU_Init(void);
void TMR0_Init(void);

void main(void) {
    MCU_Init(); //Inicializamos sistema
    while(true){
        // Display 26 alphabets
        for (num=0; num<26; num++) {
            for (repeat=0; repeat<100; repeat++){
                column = 1;
                for(count=num*8; count<(num*8+9); count++){
                    PORTB = Alphabets[count];
                    PORTC = column;
                    __delay_ms(1);
                    column = column<<1;
                }
            }
        }
        // Display 10 numbers
        for (num=0; num<10; num++) {
            for (repeat=0; repeat<100; repeat++){
                column = 1;
                for(count=num*8; count<(num*8+9); count++){
                    PORTB = Numbers[count];
                    PORTC = column;
                    __delay_ms(1);
                    column = column<<1;
                }
            }
        }
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
}
