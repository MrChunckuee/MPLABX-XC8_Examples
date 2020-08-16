/*******************************************************************************
 *
 *          Uso del sensor ultrasonico HC-SR04 
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.00
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Uso basico del sensor ultrasonico HC-SR04 
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.1     19/04/2020      - Creación del ejemplo
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <stdbool.h>
#include "word_config.h" //Only here
#include "lcd.h"

#define _XTAL_FREQ  8000000

/*********** P O R T   D E F I N I T I O N S **********************************/
#define pinTrigger      LATDbits.LATD1
#define pinTrigger_Tris TRISD1
#define pinEcho         PORTDbits.RD0
#define pinEcho_Tris    TRISD0

/************** V A R I A B L E S *********************************************/
unsigned int distance;
char lcdDistance[8];

/************** P R O T O T Y P E S *******************************************/
void MCU_Init(void);
unsigned int HCSR04_GetDistance(void);

void main(void) {
    MCU_Init();
    //Definimos el puerto y los pines donde esta la LCD
    LCD lcd = { &PORTB, 0, 1, 4, 5, 6, 7 }; // PORT, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);
    LCD_Clear();
    LCD_Set_Cursor(0,0);
    LCD_putrs(" MrChunckuee!!");
    LCD_Set_Cursor(1,0);
    LCD_putrs(" Sensor HC-SR04");
    __delay_ms(2000);
    while(1){
        distance = HCSR04_GetDistance();
        if(distance>400){
            LCD_Clear();
            LCD_Set_Cursor(0,0);
            LCD_putrs("Sensor HC-SR04");
            LCD_Set_Cursor(1,0);
            LCD_putrs("Fuera de rango");
            __delay_ms(1000);
        }
        else{
            itoa(lcdDistance, distance, 10);
            LCD_Clear();
            LCD_Set_Cursor(0,0);
            LCD_putrs("Sensor HC-SR04");
            LCD_Set_Cursor(1,0);
            LCD_puts(lcdDistance);
            LCD_Set_Cursor(1,4);
            LCD_putrs("cm");
            __delay_ms(1000);
        } 
    }
}

void MCU_Init(void){
    //Configura oscilador interno a 8MHz
    OSCCONbits.IRCF=0b111; 
    
    ADCON1=0xFF;    //Entradas digitales
    
    //Limpiamos puertos
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    
    //Todos los puertos como salidas
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
    
    pinTrigger_Tris = 0; //Output
    pinEcho_Tris = 1; //Input
}

unsigned int HCSR04_GetDistance(void){
    unsigned int centimeter=0;
    pinTrigger = 1;
    __delay_us(10);
    pinTrigger = 0;
    while(pinEcho==0); //Espera flanco de subida por el pin echo
    while(pinEcho==1){
        centimeter++;
        __delay_us(58);
    }
return(centimeter);
}
