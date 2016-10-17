/*******************************************************************************
 *
 *                  XC8_001: LED Intermitente
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC12F675
 * Complier:        XC8 v1.30
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Blinking a LED in GPIO 0, MCLR Off, INT OSC = 4MHz
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      09/05/2015      Creación del firmware
 ******************************************************************************/

#include <xc.h>
#include <pic12f675.h>

//Configuracion de FUSES del PIC12F675
#pragma config FOSC=INTRCIO //Int OSC = 4MHz
#pragma config WDTE=OFF     //Disables Watchdog Timer
#pragma config PWRTE=OFF    //Disable Power-Up Timer
#pragma config MCLRE=OFF    //Disable Master Clear
#pragma config BOREN=OFF    //Disable Blown-ou Detect
#pragma config CP=OFF       //Disable Code Protection
#pragma config CPD=OFF      //Disable Data Code Protection

#define _XTAL_FREQ 4000000 //Frecuencia de trabajo
#define LED_STATUS GPIObits.GP0

//Funciones utilizadas
void MCU_Init(void);

void main(void){
    MCU_Init();
    while(1){
        LED_STATUS ^= 1;    //Invierto el estado del LED
        __delay_ms(500);    //Retardo de 0.5 segundos
    }
}

void MCU_Init(void){
    ANSELbits.ANS=0b0000;   //Entradas y salidas digitales
    CMCONbits.CM=0b111;     //Deactivamos comparadores
    TRISIO=0x00;            //GP0 como salida, en realidad todo el puerto
    LED_STATUS=0;           //Limpio GP0 antes de cargar un valor
}
