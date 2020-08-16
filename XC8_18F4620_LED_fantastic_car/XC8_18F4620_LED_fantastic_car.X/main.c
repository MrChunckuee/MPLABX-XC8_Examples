/*******************************************************************************
 *
 *      Corrimiento de LEDs usando operador de desplazamiento
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Realizar un corriemiento en el puerto B, usando operador de 
 *                  dezplazamiento, el efecto resultante en los LEDs es el del 
 *                  auto fantastico
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     02/11/2018      - Creación del ejemplo
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <p18f4620.h>
#include "FUSES_Config.h"

//Declaramos variables y funciones globales
unsigned char count, i;
void Delay (int);

void main(void){  
    OSCCONbits.IRCF=0b001;          //Frecuencia 125KHz (ver datasheet)
    ADCON1=0x0F;                    //Hacer digitales las salidas analógicas
    TRISB=0x00;                     //RB como salida
    LATB=0x00;                      //Salidas iniciales
    while(1){
      count=1;
        for(i=0;i<=8;i++){
            LATB=count;
            count=count<<1;
            Delay(2);
        }
        count=128;
        for(i=0;i<=8;i++){
            LATB=count;
            count=count>>1;
            Delay(2);
        }   
    }
}

//Función Delay m=2ms
void Delay(int m){
    volatile int k, j;
    for(j=0; j<m; j++){
        for(k=0; k<63; k++)
        Nop();                  //Nop=1 ciclo de reloj
    }
}