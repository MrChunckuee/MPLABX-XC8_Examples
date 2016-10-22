/*******************************************************************************
 *
 *                  Libreria PCD8544
 *
 *******************************************************************************
 * FileName:        PCD8544.h
 * Processor:       PICxxxxxx
 * Complier:        XC8 v1.30
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Libreria creado para una LCD Nokia 5110, la pantalla requiere
 *                  de una comunicacion SPI pero se ha implementado una funcion
 *                  que realiza dicha tarea asique de puede usar cualquier pin
 *                  del uC.
 ******************************************************************************/
#ifndef PCD8544_H
#define	PCD8544_H

/**********P O R T * L C D * C O N F I G***************************************/
#define TRIS_pinRST     TRISB0
#define pinRST          PORTBbits.RB0 //Reset
#define TRIS_pinCE      TRISB1
#define pinCE           PORTBbits.RB1 //Chip Enable
#define TRIS_pinDC      TRISB2
#define pinDC           PORTBbits.RB2 //Data = 1 or Command = 0
#define TRIS_pinSDOUT   TRISB3
#define pinSDOUT        PORTBbits.RB3 //Data serial ouput(in LCD = DIN)
#define TRIS_pinSCLK    TRISB4
#define pinSCLK         PORTBbits.RB4 //Clock

/**********L C D * D E F I N E S***********************************************/
//The DC pin tells to LCD if we are sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA    1
//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X       84
#define LCD_Y       48

/**********G E N E R A L * D E F I N E S***************************************/
#define EYR_HIGH    1
#define EYR_LOW     0
#define EYR_OUTPUT  0

/**********P R O T O T Y P E S*************************************************/
void EYRLCD_Init(void);
void EYRLCD_Clear(void);
void EYRLCD_GotoXY(unsigned char X, unsigned char Y);
void EYRLCD_WriteByte(char DATA_CHAR);
void EYRLCD_WriteString(char *DATA_STRING, unsigned char X, unsigned char Y);
void EYRLCD_Bitmap(char MY_ARRAY[], unsigned char X, unsigned char Y);
void EYRLCD_Write(unsigned char MODE, char DATA);
void EYRLCD_WriteSPI(char outputDATA);

#endif	/* PCD8544_H */

