/*******************************************************************************
 *
 *      Control de displays de 7 segmentos con botones
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.00
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Mostramos el incremento o decremento en los diplays
 *                  RE0 incrementa, RE1 decrementa, RE2 seleciona display
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     26/04/2020      - Creación del ejemplo
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
#define readButton1 PORTEbits.RE0 
#define readButton2 PORTEbits.RE1 
#define readButton3 PORTEbits.RE2 

/************** V A R I A B L E S *********************************************/
//Variables utilizadas
unsigned char Unidad , Decena , Centena, Millar; // Para controlar vizualización del Display
unsigned int RTCC_Count;
unsigned char currentDisplayState, buttonTicks;

// Definimos constantes para el display de catodo comun
const unsigned char Display7Seg [10]={0x3F , 0x06 , 0x5B , 0x4F , 0x66 ,0x6D , 0x7D , 0x07 , 0x7F , 0x6F } ;

/************** P R O T O T Y P E S *******************************************/
void MCU_Init(void);
void RTCC_Init(void);
void GetInput(void);
void DYSPLAY7SEG_Update( void );
void DYSPLAY7SEG_Incremento( void );
void DYSPLAY7SEG_Decremento( void );

void interrupt high_priority ISR(void){
    if(INTCONbits.TMR0IF){
        ++RTCC_Count;
        if (RTCC_Count >= 20){
            DYSPLAY7SEG_Update();   // Llamamos funcion que actualiza displays
            RTCC_Count = 0;
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
        GetInput();
        __delay_ms(5);
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
    PORTE=0x00;
    
    //Todos los puertos como salidas
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
    TRISE=0b111;
    
    //Limpiamos variables globales
    Unidad = 0;
    Decena = 0;
    Centena = 0;
    Millar = 0;
 
    currentDisplayState = 0;
    
    RTCC_Count = 0;
    
    RTCC_Init();
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

void GetInput(void){
    // Push Button debounce
    // Falta mejorar rutina (se los dejo de tarea)
    if (readButton1 == 1){
        if (buttonTicks > 20){
            DYSPLAY7SEG_Incremento();
            buttonTicks = 0;
        }
        else buttonTicks++;
    }
    else if(readButton2 == 1){
        if (buttonTicks > 20){
            DYSPLAY7SEG_Decremento();
            buttonTicks = 0;
        }
        else buttonTicks++;
    }
    else if(readButton3 == 1){
        if (buttonTicks > 50){
            currentDisplayState++;
            if (currentDisplayState > 3)
                currentDisplayState = 0;
            buttonTicks = 0;
        }
        else buttonTicks++;
    }
    else buttonTicks = 0;
}

void DYSPLAY7SEG_Incremento( void ){
    switch(currentDisplayState){
        case 0:
            Unidad++;
            if (Unidad <= 0)
                Unidad = 0;
            if (Unidad > 9)
                Unidad = 0;
            break;
        case 1:
            Decena++;
            if (Decena <= 0)
                Decena = 0;
            if (Decena > 9)
                Decena = 0;
            break;
        case 2:
            Centena++;
            if (Centena <= 0)
                Centena = 0;
            if (Centena > 9)
                Centena = 0;
            break;
        case 3:
            Millar++;
            if (Millar <= 0)
                Millar = 0;
            if (Millar > 9)
                Millar = 0;
            break;
        default:
            Unidad = 0;
            Decena = 0;
            Centena = 0;
            Millar = 0;
            break;
    }
}

void DYSPLAY7SEG_Decremento( void ){
    switch(currentDisplayState){
        case 0:
            Unidad--;
            if (Unidad <= 0)
                Unidad = 0;
            if (Unidad > 9)
                Unidad = 0;
            break;
        case 1:
            Decena--;
            if (Decena <= 0)
                Decena = 0;
            if (Decena > 9)
                Decena = 0;
            break;
        case 2:
            Centena--;
            if (Centena <= 0)
                Centena = 0;
            if (Centena > 9)
                Centena = 0;
            break;
        case 3:
            Millar--;
            if (Millar <= 0)
                Millar = 0;
            if (Millar > 9)
                Millar = 0;
            break;
        default:
            Unidad = 0;
            Decena = 0;
            Centena = 0;
            Millar = 0;
            break;
    }
}

void DYSPLAY7SEG_Update ( void ){
	// Cargamos en puerto valor de la tabla indicado por Unidad 
	LATD = Display7Seg [Unidad];
	ctrlUnidadTransistor  = 1; // Enciendo Display Unidad
	__delay_ms(1);
	ctrlUnidadTransistor  = 0;
	LATD = Display7Seg [Decena];
	 ctrlDecenaTransistor  = 1;
	__delay_ms(1);  
	 ctrlDecenaTransistor  = 0;
	LATD = Display7Seg [Centena];
	ctrlCentenaTransistor = 1;
	__delay_ms(1);  
	ctrlCentenaTransistor = 0; // Apago Display Centena
	LATD = Display7Seg [Millar];
	ctrlMillarTransistor  = 1;
	__delay_ms(1); 
	ctrlMillarTransistor  = 0;
}