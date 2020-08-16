/*******************************************************************************
 *
 *      Contador con display de 7 segmentos catodo común
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Mostramos numeros en forma ascecenden y descendente en el 
 *                  modulo de display de 7 segmentos, aproximadamente casa 0.7 
 *                  segundos es el incremento.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     09/01/2020      - Creación del ejemplo
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <stdbool.h>
#include "word_config.h" //Only here

#define _XTAL_FREQ  16000000

/*********** P O R T   D E F I N I T I O N S **********************************/
#define ctrlUnidadTransistor  LATBbits.LATB0
#define ctrlDecenaTransistor  LATBbits.LATB1
#define ctrlCentenaTransistor LATBbits.LATB2
#define ctrlMillarTransistor  LATBbits.LATB3

/************** V A R I A B L E S *********************************************/
unsigned char i;

// Definimos constantes para el display de catodo comun
const unsigned char Display7Seg [10]={0x3F , 0x06 , 0x5B , 0x4F , 0x66 ,0x6D , 0x7D , 0x07 , 0x7F , 0x6F } ;

/************** P R O T O T Y P E S *******************************************/
void MCU_Init(void);

void main(void) {
    MCU_Init();
    while(1){
        for(i=0; i<=9;  i++){
            LATD = Display7Seg [i];
            __delay_ms(700);	// 0.7 second delay
        }
        for(i=8; i>0;  i--){
            LATD = Display7Seg [i];
            __delay_ms(700);	// 0.7 second delay
        }
    }
}

void MCU_Init(void){
    //Configura oscilador interno a 4MHz
    OSCCONbits.IRCF=0b110; 
    OSCTUNEbits.PLLEN = 1;      //PLL enable Fosc = 16MHz
    
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
    
    //Encendemos todos los displays
    ctrlUnidadTransistor  = 1;
    ctrlDecenaTransistor  = 1;
    ctrlCentenaTransistor = 1;
    ctrlMillarTransistor  = 1;
}