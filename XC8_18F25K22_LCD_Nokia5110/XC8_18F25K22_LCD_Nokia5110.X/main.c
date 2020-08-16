/*******************************************************************************
 *
 *                  Control de LCD Nokia 5110
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Probando libreria para LCD Nokia5110, para cambiar la
 *                  distribucion de pines modificar en PCD8544.h
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      20/02/2016      Creación del firmware
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f25k22.h>
#include "Config_FusesPIC.h" //Only here
#include "PCD8544.h"

#define _XTAL_FREQ 8000000

extern const unsigned char EYR_ImageLogo[];
unsigned char DISPLAY_COUNT[4];
unsigned int ACC;

void MCU_Init(void);
void Delay_ms(unsigned int t);
void MCU_MensajeInicio(void);
void MCU_DisplayUpdate(void);

void main(void){
    MCU_Init();
    EYRLCD_Init();
    EYRLCD_Clear();
    Delay_ms(10);
    ACC=0;
    MCU_MensajeInicio();
    while(1){
        ACC++;
        if (ACC>1234){
            DISPLAY_COUNT[0]='0';
            DISPLAY_COUNT[1]='0';
            DISPLAY_COUNT[2]='0';
            DISPLAY_COUNT[3]='0';
            ACC=0;
        }
        itoa(DISPLAY_COUNT, ACC, 10);
        MCU_DisplayUpdate();
        Delay_ms(100);
    }
}

void MCU_Init(void){
    ANSELA=0x00; //all digital
    ANSELB=0x00; //all digital
    ANSELC=0x00; //all digital
    OSCCONbits.IRCF=0b110; //Fosc=8MHz
    TRISB=0x00; //PORTB output
}

void Delay_ms(unsigned int t){
    unsigned int j;
    for(j=0;j<t;j++){
        __delay_ms(1);
    }
}

void MCU_MensajeInicio(void){
   //Mensaje de inicio
    EYRLCD_Bitmap(EYR_ImageLogo, 0, 0);
    Delay_ms(3000);
    EYRLCD_Clear();
    EYRLCD_WriteString("Libreria LCD", 0, 0);
    EYRLCD_WriteString("Nokia 5110", 0, 9);
    EYRLCD_WriteString("Contador", 0, 18);
    EYRLCD_WriteString("MrChunckuee", 0, 27);
    EYRLCD_WriteString("MPLABX & XC8", 0, 36);
    Delay_ms(3000);
    DISPLAY_COUNT[0]='0';
    DISPLAY_COUNT[1]='0';
    DISPLAY_COUNT[2]='0';
    DISPLAY_COUNT[3]='0';
    EYRLCD_Clear();
}

void MCU_DisplayUpdate(void){
    EYRLCD_Clear();
    EYRLCD_WriteString("Conteo:", 0, 0);
    if (ACC<10){
            EYRLCD_GotoXY(0, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[0]);
        }
        else if (ACC>=10 && ACC<100){
            EYRLCD_GotoXY(0, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[0]);
            EYRLCD_GotoXY(10, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[1]);
        }
        else if(ACC >=100 && ACC<1000){
            EYRLCD_GotoXY(0, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[0]);
            EYRLCD_GotoXY(10, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[1]);
            EYRLCD_GotoXY(20, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[2]);
        }
        else if(ACC>=1000){
            EYRLCD_GotoXY(0, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[0]);
            EYRLCD_GotoXY(10, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[1]);
            EYRLCD_GotoXY(20, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[2]);
            EYRLCD_GotoXY(30, 10);
            EYRLCD_WriteByte(DISPLAY_COUNT[3]);
        }
}

