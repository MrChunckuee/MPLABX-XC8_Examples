/* 
 * File:   lcd.h
 * Author: MrChunckuee
 *
 * Created on 19 de julio de 2017, 10:00 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

//// Macros that correspond to LCD commands
//#define LCD_Clear()                 LCD_Cmd(0x01)
//#define LCD_Decrement_Cursor()      LCD_Cmd(0x04)
//#define LCD_Increment_Cursor()      LCD_Cmd(0x05)
//#define LCD_Shift_Display_Right()   LCD_Cmd(0x06)
//#define LCD_Shift_Display_Left()    LCD_Cmd(0x07)
//#define LCD_Shift_Right()           LCD_Cmd(0x1C)
//#define LCD_Shift_Left()            LCD_Cmd(0x18)
//
//// Sets the LCD cursor position
//#define LCD_Set_Cursor(x, y)             \
//do {                                     \
//    if ( x == 0 ) {                      \
//        LCD_Cmd(0x80 + y);               \
//    }                                    \
//    else if ( x == 1 ) {                 \
//        LCD_Cmd(0xC0 + y);               \
//    }                                    \
//    else if ( x == 2 ) {                 \
//        LCD_Cmd(0x94 + y);               \
//    }                                    \
//    else if ( x == 3 ) {                 \
//        LCD_Cmd(0xD4 + y);               \
//    }                                    \
//} while(false)
//
//// [Internal use only] Sets the display on/off, the cursor on/off and if it will blink or not
//#define LCD_Display( on, cursor, blink ) \
//do {                                     \
//    unsigned char cmd = 0x08;            \
//                                         \
//    if ( on == true ) {                  \
//        cmd |= 1 << 2;                   \
//    }                                    \
//                                         \
//    if ( cursor == true ) {              \
//        cmd |= 1 << 1;                   \
//    }                                    \
//                                         \
//    if ( blink == true ) {               \
//        cmd |= 1;                        \
//    }                                    \
//                                         \
//    LCD_Cmd(cmd);                        \
//} while ( false )
//
//// [Internal use only] Sends a command to the LCD
//#define LCD_Cmd( c )                     \
//do {                                     \
//    LCD_Write( (c & 0xF0) >> 4 );        \
//    LCD_Write( c & 0x0F);                \
//} while ( false )
//
//// Initializes the LCD (See LCD struct)
//bool LCD_Init ( LCD display );
//
//// Prints a character on the LCD
//void LCD_putc ( char a );
//
//// Prints a string on the LCD that is allocated on the RAM
//void LCD_puts ( char *a );
//
//// Prints a string on the LCD that is allocated on the program memory
//void LCD_putrs ( const char *a );
//
//// [Internal use only] Write a byte to the LCD
//void LCD_Write ( unsigned char c );
//
//// [Internal use only] Outputs the data to the LCD Port
//void LCD_Out ( char a );
    
/*********** L C D   P O R T   D E F I N I T I O N S **************************/
#define LCD_RS      PORTDbits.RD0
#define LCD_E       PORTDbits.RD1
#define LCD_D4      PORTDbits.RD4
#define LCD_D5      PORTDbits.RD5
#define LCD_D6      PORTDbits.RD6
#define LCD_D7      PORTDbits.RD7
#define LCD_PORT    PORTD
#define LCD_TRIS    TRISD
    
/*********** G E N E R A L   D E F I N I T I O N S **************************/
#define	LCD_OFF             8
#define LCD_ON              12
#define	LCD_CURSOR_ON       14
#define	LCD_CURSOR_OFF      12
#define	LCD_CURSOR_BLINK    15
#define	LCD_CURSOR_NOBLINK  14
#define	LCD_CLEAR_SCREEN    1
#define LCD_HOME            2
#define	LCD_LINE1           0x80
#define	LCD_LINE2           0xC0
#define	LCD_LINE3           0x90
#define	LCD_LINE4           0xD0
#define	LCD_SPACE_ASCII     0x20

#define LCD_Clear()     LCD_WriteCommand(LCD_CLEAR_SCREEN)

/************** P R O T O T Y P E S *******************************************/
void LCD_Init(void);
void LCD_Strobe(void);

void LCD_WriteNibble(char LCD_COMMAND);
void LCD_WriteCommand(char LCD_COMMAND);
void LCD_WriteData(char LCD_DATA);
void LCD_Putc_xy(char LCD_DATA,char LCD_X,char LCD_Y);
void LCD_GotoXY(char LCD_X,char LCD_Y);
void LCD_ClearSpace(char LCD_X,char LCD_Y,char LCD_WIDE);
void LCD_ClearLine(char LCD_Y);
void LCD_Puts(char *LCD_STRING,char LCD_X,char LCD_Y);
void LCD_Putrs(const char *LCD_STRING,char LCD_X,char LCD_Y);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */