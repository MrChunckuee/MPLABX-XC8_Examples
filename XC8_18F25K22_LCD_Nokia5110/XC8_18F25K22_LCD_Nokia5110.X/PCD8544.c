/*******************************************************************************
 *
 *                  Libreria PCD8544
 *
 *******************************************************************************
 * FileName:        PCD8544.c
 * Processor:       PICxxxxxx
 * Complier:        XC8 v1.30
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Libreria creado para una LCD Nokia 5110, la pantalla requiere
 *                  de una comunicacion SPI pero se ha implementado una funcion
 *                  que realiza dicha tarea asique de puede usar cualquier pin
 *                  del uC.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      20/02/2016      Creación del firmware
 ******************************************************************************/
#include <xc.h>
#include "PCD8544.h"
#include "font_pattern.h"
#include <pic18f25k22.h> //Cambiar por el PIC a usar

/*******************************************************************************
 * Function:        void EYRLCD_Init(void)
 * Description:     This function init the LCD, sends the magical commands to the PCD8544
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_Init(void){
    //Configure control pins
    TRIS_pinRST=EYR_OUTPUT;
    TRIS_pinCE=EYR_OUTPUT;
    TRIS_pinDC=EYR_OUTPUT;
    TRIS_pinSDOUT=EYR_OUTPUT;
    TRIS_pinSCLK=EYR_OUTPUT;
    pinCE=EYR_HIGH;
    //Reset the LCD to a known state
    pinRST=EYR_LOW;
    Nop(); //Delay = 0.5uS when FOSC=8MHz, Datasheet twl_min=100nS
    pinRST=EYR_HIGH;
    EYRLCD_Write(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
    EYRLCD_Write(LCD_COMMAND, 0xB0); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
    EYRLCD_Write(LCD_COMMAND, 0x04); //Set Temp coefficent
    EYRLCD_Write(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14
    EYRLCD_Write(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
    EYRLCD_Write(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse
}

/*******************************************************************************
 * Function:        void EYRLCD_Clear(void)
 * Description:     This function clears the LCD by writing zeros to the entire screen
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_Clear(void){
    for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    EYRLCD_Write(LCD_DATA, 0x00);
    EYRLCD_GotoXY(0, 0); //After we clear the display, return to the home position
}

/*******************************************************************************
 * Function:        void EYRLCD_GotoXY(unsigned char X, unsigned char Y)
 * Description:     This function set X & Y value
 * Precondition:    None
 * Parameters:      unsigned char X & unsigned char Y
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_GotoXY(unsigned char X, unsigned char Y){
    EYRLCD_Write(LCD_COMMAND, 0x80 | X);  // Column.
    EYRLCD_Write(LCD_COMMAND, 0x40 | Y);  // Row.
}

/*******************************************************************************
 * Function:        void EYRLCD_WriteByte(char DATA_CHAR)
 * Description:     This function takes in a character, looks it up in the font
 *                  table/array. And writes it to the screen. Each character
 *                  is 8 bits tall and 5 bits wide. We pad one blank column of
 *                  pixels on each side of the character for readability.
 * Precondition:    None
 * Parameters:      char DATA_CHAR
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_WriteByte(char DATA_CHAR){
    EYRLCD_Write(LCD_DATA, 0x00); //Blank vertical line padding
    for (int index = 0 ; index < 5 ; index++)
        EYRLCD_Write(LCD_DATA, FONT_1[DATA_CHAR - 0x20][index]);
    //0x20 is the ASCII character for Space (' '). The font table starts with this character
    EYRLCD_Write(LCD_DATA, 0x00); //Blank vertical line padding
}

/*******************************************************************************
 * Function:        void EYRLCD_WriteString(char *DATA_STRING, unsigned char X, unsigned char Y)
 * Description:     Given a string of characters, one by one is passed to the LCD
 * Precondition:    None
 * Parameters:      unsigned char X & unsigned char Y
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_WriteString(char *DATA_STRING, unsigned char X, unsigned char Y){
    EYRLCD_GotoXY(X, Y);
    while (*DATA_STRING)
    EYRLCD_WriteByte(*DATA_STRING++);
}

/*******************************************************************************
 * Function:        void EYRLCD_Bitmap(char MY_ARRAY[])
 * Description:     This takes a large array of bits and sends them to the LCD
 * Precondition:    None
 * Parameters:      MY_ARRAY[] tt contains the bitmap to send
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_Bitmap(char MY_ARRAY[], unsigned char X, unsigned char Y){
    EYRLCD_GotoXY(X, Y);
    for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    EYRLCD_Write(LCD_DATA, MY_ARRAY[index]);
}

/*******************************************************************************
 * Function:        void EYRLCD_Write(unsigned char MODE, char DATA)
 * Description:     There are two memory banks in the LCD, data/RAM and commands.
 *                  This function sets the DC pin high or low depending,
 *                  and then sends the data byte
 * Precondition:    None
 * Parameters:      MODE = Say to the LCD that we are writing either data or commands
 *                  DATA = data for LCD
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_Write(unsigned char MODE, char DATA){
    pinDC=MODE;
    //Send the data or a command
    pinCE=EYR_LOW;
    EYRLCD_WriteSPI(DATA);
    pinCE=EYR_HIGH;
}

/*******************************************************************************
 * Function:        void EYRLCD_WriteSPI(char outputDATA)
 * Description:     This function emulates the SPI communication and writes
 *                  data to the LCD
 * Precondition:    None
 * Parameters:      outputDATA = data for LCD
 * Return Values:   None
 * Remarks:         None
 * ****************************************************************************/
void EYRLCD_WriteSPI(char outputDATA){
    unsigned char BitCount;
    for (BitCount=0; BitCount<8; BitCount++){
        pinSCLK=EYR_LOW;
        if ((outputDATA&0x80)==0)
            pinSDOUT=EYR_LOW;
        else
            pinSDOUT=EYR_HIGH;
        pinSCLK=EYR_HIGH;
        outputDATA=outputDATA<<1;
    }
}