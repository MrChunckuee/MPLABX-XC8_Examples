#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "lcd.h"

#define _XTAL_FREQ 16000000

/*******************************************************************************
 * Function:        void LCD_Init(void)
 * Description:     This function initilizes the LCD
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void LCD_Init(void){
    // Send reset signal to the LCD
    __delay_ms(20);
    LCD_WriteNibble(0x03);
    __delay_ms(5);
    LCD_WriteNibble(0x03);
    LCD_WriteNibble(0x03);
    // Specify the data lenght to 4 bits
    LCD_WriteNibble(0x02);
    LCD_WriteCommand(0x20);
    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCD_WriteCommand(0x28);
    LCD_WriteCommand(0x14);
    LCD_WriteCommand(0x0F);
    LCD_WriteCommand(0x01);
    // Set cursor to move from left to right
    LCD_WriteCommand(0x06);
    LCD_WriteCommand(LCD_ON);
    __delay_ms(20);
    LCD_WriteCommand(LCD_CURSOR_OFF);
    //Escribe caracter definido en la CGRAM
    LCD_WriteCommand(0x40);
    LCD_WriteData(0x08);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x08);
    LCD_WriteData(0x00);
    LCD_WriteCommand(LCD_HOME);   
}

/*******************************************************************************
 * Function:        void LCD_Strobe(void)
 * Description:     Generates a sync pulse to write data to the display
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void LCD_Strobe(void){
    LCD_E=1;
    __delay_us(1);
    LCD_E=0;
    __delay_us(1);
}


void LCD_WriteNibble(char LCD_COMMAND){
char LCD_PORT_DATA=0;
LCD_E=0;
LCD_RS=0;
LCD_PORT=(LCD_PORT&(0x0F));
LCD_PORT_DATA=((0x0F)&LCD_COMMAND)<<4;
LCD_PORT|=LCD_PORT_DATA;
LCD_Strobe();
__delay_ms(2);
}

/**
  * @brief  Escribe un comando en el lcd alfanumerico
  * @param  LCD_COMMAND: comando enviado al display alfanumerico
  * @param  None
  * @retval None
  */
void LCD_WriteCommand(char LCD_COMMAND)
{
char LCD_PORT_DATA=0;
LCD_E=0;
LCD_RS=0;
LCD_PORT=(LCD_PORT&(0x0F));
LCD_PORT_DATA=((0xF0)&LCD_COMMAND);
LCD_PORT|=LCD_PORT_DATA;
LCD_Strobe();
LCD_PORT=(LCD_PORT&(0x0F));
LCD_PORT_DATA=((0x0F)&LCD_COMMAND)<<4;
LCD_PORT|=LCD_PORT_DATA;
LCD_Strobe();
__delay_us(45);
if((LCD_COMMAND==LCD_HOME)||(LCD_COMMAND==LCD_CLEAR_SCREEN))
__delay_ms(2);
}


/**
  * @brief  Escribe un dato en el lcd alfanumerico
  * @param  LCD_DATA: dato enviado al display alfanumerico
  * @param  None
  * @retval None
  */
void LCD_WriteData(char LCD_DATA)
{
char LCD_PORT_DATA=0;
LCD_E=0;
LCD_RS=1;
LCD_PORT=(LCD_PORT&(0x0F));
LCD_PORT_DATA=((0xF0)&LCD_DATA);
LCD_PORT|=LCD_PORT_DATA;
LCD_Strobe();
LCD_PORT=(LCD_PORT&(0x0F));
LCD_PORT_DATA=((0x0F)&LCD_DATA)<<4;
LCD_PORT|=LCD_PORT_DATA;
LCD_Strobe();
__delay_us(45);
}


/**
  * @brief  Escribe un comando en el lcd alfanumerico
  * @param  LCD_DATA: dato enviado al display alfanumerico
  * @param  LCD_X: columna en la que se desea colocar un caracter en el display
  * @param  LCD_Y: fila en la que se desea colocar un caracter en el display
  * @retval None
  */
void LCD_Putc_xy(char LCD_DATA,char LCD_X,char LCD_Y)
{
LCD_GotoXY(LCD_X,LCD_Y);
LCD_WriteData(LCD_DATA);
}






/**
  * @brief  Coloca el cursor en la fila y columna indicada
  * @param  LCD_X: Columna donde se desea colocar el cursor
  * @param 	LCD_Y: Fila donde se desea colocar el cursor
  * @retval None
  */
void LCD_GotoXY(char LCD_X,char LCD_Y)
{

switch(LCD_Y)
	{
	case 0:
	LCD_WriteCommand(LCD_LINE1+LCD_X);
	break;
	case 1:
	LCD_WriteCommand(LCD_LINE2+LCD_X);
	break;
	case 2:
	LCD_WriteCommand(LCD_LINE3+LCD_X);
	break;
	case 3:
	LCD_WriteCommand(LCD_LINE4+LCD_X);
	break;
	default:
	break;
	}

}



/**
  * @brief  Genera LCD_WIDE espacios en blanco comenzando en la fila LCD_Y y la columna LCD_X
  * @param  LCD_X: Columna donde se desea colocar el primer espacio en balnco
  * @param  LCD_Y: Fila donde se desea colocar el primer espacio en balnco
  * @param  LCD_WIDE: Cantidad de espacios en blanco que se desea colocar
  * @retval None
  */
void LCD_ClearSpace(char LCD_X,char LCD_Y,char LCD_WIDE)
{
char LCD_SPACE_COUNT=0;
char LCD_WIDE_COUNT=LCD_WIDE;
LCD_SPACE_COUNT=16-LCD_X;
	if((LCD_SPACE_COUNT>0)&&(LCD_SPACE_COUNT<4))
	{
		LCD_GotoXY(LCD_X,LCD_Y);
		do
		{
		LCD_WriteData(LCD_SPACE_ASCII);
		LCD_WIDE_COUNT--;
		LCD_SPACE_COUNT--;
		}
		while(LCD_WIDE_COUNT&&LCD_SPACE_COUNT);
	}
LCD_GotoXY(LCD_X,LCD_Y);
}



/**
  * @brief  Limpia la linea indicada por LCD_Y
  * @param  LCD_Y: Fila en donde se desea limpiar la linea
  * @param  None
  * @retval None
  */
void LCD_ClearLine(char LCD_Y)
{

char LCD_SPACE_COUNT=16;

switch(LCD_Y)
	{
	case 0:
	LCD_WriteCommand(LCD_LINE1);
	break;
	case 1:
	LCD_WriteCommand(LCD_LINE2);
	break;
	case 2:
	LCD_WriteCommand(LCD_LINE3);
	break;
	case 3:
	LCD_WriteCommand(LCD_LINE4);
	break;
	default:
	break;
	}

	do
	{
	LCD_WriteData(LCD_SPACE_ASCII);
	LCD_SPACE_COUNT--;
	}
	while(LCD_SPACE_COUNT);
}



/**
  * @brief  Coloca una cadena ubicada en RAM en la fila LCD_Y y la columna LCD_X
  * @param  *LCD_STRING: Dirección de la cadena en RAM
  * @param  LCD_X: Columna donde se desea colocar el primer caracter
  * @param  LCD_Y: Linea donde se colocara la cadena
  * @retval None
  */
void LCD_Puts(char *LCD_STRING,char LCD_X,char LCD_Y)
{
char LCD_INDEX=0;
char LCD_WIDE_COUNT=0;

LCD_WIDE_COUNT=16-LCD_X;

LCD_GotoXY(LCD_X,LCD_Y);

	for(LCD_INDEX=0;(*(LCD_STRING+LCD_INDEX)&&LCD_WIDE_COUNT);LCD_INDEX++,LCD_WIDE_COUNT--)
	LCD_WriteData(*(LCD_STRING+LCD_INDEX));


}


/**
  * @brief  Coloca una cadena ubicada en FLASH en la fila LCD_Y y la columna LCD_X
  * @param  *LCD_STRING: Dirección de la cadena en FLASH
  * @param  LCD_X: Columna donde se desea colocar el primer caracter
  * @param  LCD_Y: Linea donde se colocara la cadena
  * @retval None
  */
void LCD_Putrs(const char *LCD_STRING,char LCD_X,char LCD_Y)
{
char LCD_INDEX=0;
char LCD_WIDE_COUNT=0;

LCD_WIDE_COUNT=16-LCD_X;

LCD_GotoXY(LCD_X,LCD_Y);

	for(LCD_INDEX=0;(*(LCD_STRING+LCD_INDEX)&&LCD_WIDE_COUNT);LCD_INDEX++,LCD_WIDE_COUNT--)
	LCD_WriteData(*(LCD_STRING+LCD_INDEX));

}


/*
 * File: lcd.c
 *
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 *
 * LCD library source file.
 * 
 * https://github.com/magkopian/pic-xc8-lcd-library
 * 
 */

//Se agrego la opcion para el PIC18F4620

//#include <stdbool.h>
//#include <xc.h>
//#include "lcd.h"
//
//#define _XTAL_FREQ 16000000
//
//LCD lcd;
//
//void LCD_Out ( char c ) {
//    if ( c & 1 ){
//        *(lcd.PORT) |= 1 << lcd.D4;
//    }
//    else {
//         *(lcd.PORT) &= ~(1 << lcd.D4);
//    }
//
//    if ( c & 2 ) {
//        *(lcd.PORT) |= 1 << lcd.D5;
//    }
//    else {
//        *(lcd.PORT) &= ~(1 << lcd.D5);
//    }
//
//    if ( c & 4 ) {
//        *(lcd.PORT) |= 1 << lcd.D6;
//    }
//    else {
//        *(lcd.PORT) &= ~(1 << lcd.D6);
//    }
//
//    if ( c & 8 ) {
//         *(lcd.PORT) |= 1 << lcd.D7;
//    }
//    else {
//         *(lcd.PORT) &= ~(1 << lcd.D7);
//    }
//
//}
//
//void LCD_Write ( unsigned char c ) {
//    *(lcd.PORT) &= ~(1 << lcd.RS); // => RS = 0
//    LCD_Out(c);
//    *(lcd.PORT) |= 1 << lcd.EN;    // => E = 1
//    __delay_ms(4);
//    *(lcd.PORT) &= ~(1 << lcd.EN); // => E = 0
//}
//
//bool LCD_Init ( LCD display ) {
//
//    lcd = display;
//
//    /*
//     * TODO:
//     * The function should clear only the appropriate bits, not the whole PORT
//     *
//     * TODO:
//     * "#if defined" needs to support more microcontrollers that have PORTD and PORTE
//     */
//    if ( lcd.PORT == &PORTA ) {
//        TRISA = 0x00;
//    }
//    else if ( lcd.PORT == &PORTB ) {
//        TRISB = 0x00;
//    }
//    else if ( lcd.PORT == &PORTC ) {
//        TRISC = 0x00;
//    }
//    #if defined(_16F877) || defined(_16F877A) || defined(_18F4620)
//    else if ( lcd.PORT == &PORTD ) {
//        TRISD = 0x00;
//    }
//    else if ( lcd.PORT == &PORTE ) {
//        TRISE = 0x00;
//    }
//    #endif
//    else {
//        return false;
//    }
//
//    // Give some time to the LCD to start function properly
//    __delay_ms(20);
//
//    // Send reset signal to the LCD
//    LCD_Write(0x03);
//    __delay_ms(5);
//    LCD_Write(0x03);
//    __delay_ms(16);
//    LCD_Write(0x03);
//
//    // Specify the data lenght to 4 bits
//    LCD_Write(0x02);
//
//    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
//    LCD_Cmd(0x28);
//
//    // Set cursor to move from left to right
//    LCD_Cmd(0x06);
//
//    LCD_Display(true, false, false); // Turn on display and set cursor off
//    
//
//    LCD_Clear();
//    
//    return true;
//}
//
//void LCD_putc ( char c ) {
//
//   *(lcd.PORT) |= 1 << lcd.RS;   // => RS = 1
//    LCD_Out((c & 0xF0) >> 4);    //Data transfer
//
//    *(lcd.PORT) |= 1 << lcd.EN;
//    __delay_us(40);
//    *(lcd.PORT) &= ~(1 << lcd.EN);
//    
//    LCD_Out(c & 0x0F);
//    *(lcd.PORT) |= 1 << lcd.EN;
//    __delay_us(40);
//    *(lcd.PORT) &= ~(1 << lcd.EN);
//    
//
//}
//
//void LCD_puts ( char *a ) {
//
//    for ( int i = 0; a[i] != '\0'; ++i ) {
//        LCD_putc(a[i]);
//    }
//
//}
//
//void LCD_putrs ( const char *a ) {
//
//    for ( int i = 0; a[i] != '\0'; ++i ) {
//        LCD_putc(a[i]);
//    }
//
//}
