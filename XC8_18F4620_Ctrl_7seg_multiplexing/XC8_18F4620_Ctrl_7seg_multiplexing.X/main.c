/*******************************************************************************
 *
 *      Control de 4 displays de 7 segmentos con multiplexación
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Mostramos numeros de forma ascecenden en el modulo de 
 *                  display de 7 segmentos, haciendo uso de la multiplexacion 
 *                  contamos hasta 9999 y luego se resetea el contador.
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
//Variables utilizadas
unsigned char i, Unidad , Decena , Centena, Millar; // Para controlar vizualización del Display

// Definimos constantes para el display de catodo comun
const unsigned char Display7Seg [10]={0x3F , 0x06 , 0x5B , 0x4F , 0x66 ,0x6D , 0x7D , 0x07 , 0x7F , 0x6F } ;

/************** P R O T O T Y P E S *******************************************/
void MCU_Init(void);
void DYSPLAY7SEG_Update( void );

void main(void) {
    MCU_Init();
    while(1){
        // Llamamos funcion que actualiza displays
        DYSPLAY7SEG_Update();
        // Actualizamos cuenta 
        ++ Unidad ;
        if( Unidad ==10){
            Unidad =0;
            ++ Decena ;
            if( Decena ==10){
                Decena =0;
                ++ Centena ;
                if(Centena==10){
                    Centena=0;
                    ++Millar;
                    if(Millar==10){
                        Millar=0;
                    }
                }
            }
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
    
    //Limpiamos variables globales
    Unidad = 0;
    Decena = 0;
    Centena = 0;
    Millar = 0;
}

void DYSPLAY7SEG_Update ( void ){
    //El for es para crear el retardo para cada incremento, incrementar o 
    //decrementar i provoca que la actualizacion sea mas grande o mas pequeño
    //ahora mismo el retado vale 20ms x 5 = 100ms
	for (i =0; i <=5; ++ i){ 
	// Cargamos en puerto valor de la tabla indicado por Unidad 
	LATD = Display7Seg [Unidad];
	ctrlUnidadTransistor  = 1; // Enciendo Display Unidad
	__delay_ms(5);  //delay 5 ms
	ctrlUnidadTransistor  = 0;
	LATD = Display7Seg [Decena];
	 ctrlDecenaTransistor  = 1;
	__delay_ms(5);  //delay 5 ms
	 ctrlDecenaTransistor  = 0;
	LATD = Display7Seg [Centena];
	ctrlCentenaTransistor = 1;
	__delay_ms(5);  //delay 5 ms
	ctrlCentenaTransistor = 0; // Apago Display Centena
	LATD = Display7Seg [Millar];
	ctrlMillarTransistor  = 1;
	__delay_ms(5);  //delay 5 ms
	ctrlMillarTransistor  = 0;
	}
}