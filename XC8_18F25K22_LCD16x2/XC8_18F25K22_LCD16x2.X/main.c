/*******************************************************************************
 *
 *                  Uso de la libreria LCD
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Probando libreria para LCD 16x2, debo mencionar que no soy el
 *                  autor original de la libreria solo hago uso de ella, en la 
 *                  cabecera de lcd.c esta el enlace a su GitHub
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      03/02/2017      Creación del ejemplo
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include "FUSES_Config.h" //Only here
#include "lcd.h"

#define _XTAL_FREQ  16000000
#define LED_1       PORTCbits.RC6

unsigned int RTCC_Count = 0;
char text_1[] = "  MrChunckuee!  ";
char text_2[] = "http://mrchunckuee.blogspot.com/";

void MCU_Init(void);
void MCU_Delayms(unsigned int time);
void RTCC_Init(void);

void interrupt high_priority ISR(void){
    if(INTCONbits.TMR0IF){
        ++RTCC_Count;
        if (RTCC_Count >= 1000){
            LED_1 ^= 1; //Blink LED
            RTCC_Count = 0;
        }
        TMR0H = 0xF8;
        TMR0L = 0x30;
        INTCONbits.TMR0IF = 0;
        return;
    }
}

int main ( void ) {
    MCU_Init();
    //Definimos el puerto y los pines donde esta la LCD
    LCD lcd = { &PORTB, 0, 1, 4, 5, 6, 7 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear();
    while(true) {
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs(" LCD 16x2 & XC8 ");
        LCD_Set_Cursor(1,0);
        for(char c = 0; c<15; ++c){
            LCD_putc(text_1[c]);
            MCU_Delayms(300);
        }        
        MCU_Delayms(1000); // Delay 1s  
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        for(char c = 0; c<16; ++c){
            LCD_putc(text_2[c]);
            MCU_Delayms(300);
        }
        LCD_Set_Cursor(1,0);
        for(char c = 16; c<32; ++c){
            LCD_putc(text_2[c]);
            MCU_Delayms(300);
        }
        MCU_Delayms(1000); // Delay 1s   
	}
}

void MCU_Init(void){
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    //Configura oscilador interno a 16MHz
    OSCCONbits.IRCF=0b111; //El ciclo de instruccion es de 0.25 us
    TRISCbits.RC6 = 0; //Pin del LED como salida
    RTCC_Init();
}

void MCU_Delayms(unsigned int time){
    unsigned int acc;
    for(acc=0; acc<time; acc++){
        __delay_ms(1);
    }
}

void RTCC_Init(void){
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