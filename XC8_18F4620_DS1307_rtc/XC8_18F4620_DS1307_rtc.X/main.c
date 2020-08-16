/*******************************************************************************
 *
 *      Probando el modulo Tiny RTC DS1307
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F4620
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Prueba de libreria para el RTC DS1307
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     10/07/2017      - Creación del ejemplo
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <stdbool.h>
#include "word_config.h" //Only here
#include "lcd.h"
#include "i2c.h"
#include "ds1307.h"

#define _XTAL_FREQ  16000000

/*********** P O R T   D E F I N I T I O N S **********************************/
#define LED1    PORTEbits.RE0
#define LED2    PORTEbits.RE1
#define LED3    PORTEbits.RE2

/************** V A R I A B L E S *********************************************/


/************** P R O T O T Y P E S *******************************************/
void MCU_Init(void);
void MCU_HelloMessage(void);
void DisplayTimeToLCD( unsigned char* pTimeArray );
void DisplayDateOnLCD( unsigned char* pDateArray );

void main(void) {
    MCU_Init();
    LCD_Init();
	InitI2C();	// Initialize i2c pins											
	// Set initial time
	Set_DS1307_RTC_Time(PM_Time, 11, 59, 55);	// Set time 11:30:00 PM
	// Set initial date
	Set_DS1307_RTC_Date(25, 07, 17, Tuesday); 	// Set 25-07-2017 @ Tuesday
    
    MCU_HelloMessage();
    while(true){
//        LCD_Clear();
        // Display RTC time on first line of LCD
		DisplayTimeToLCD(Get_DS1307_RTC_Time());
		// Display RTC date on second line of LCD
		DisplayDateOnLCD(Get_DS1307_RTC_Date());
		__delay_ms(1000);	// 1 second delay
    }
}

void MCU_Init(void){
    //Configura oscilador interno a 4MHz
    OSCCONbits.IRCF=0b110; 
    OSCTUNEbits.PLLEN = 1;      //PLL enable Fosc = 16MHz
    
    ADCON1=0xFF;    //Entradas digitales
    
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
}

void MCU_HelloMessage(void){
    LCD_Clear();
    LCD_Putrs("  MrChunckuee!  ",0,0);
    LCD_Putrs("RTC: DS1307 demo",0,1);
    __delay_ms(2000);	// 1 second delay
    LCD_Clear();
}

void DisplayTimeToLCD(unsigned char* pTimeArray){   // Displays time in HH:MM:SS AM/PM format  
	// Display Hour
	LCD_Putc_xy( (pTimeArray[2]/10)+0x30, 0, 0 );
    LCD_Putc_xy( (pTimeArray[2]%10)+0x30, 1, 0 );
	LCD_Putrs(":", 2, 0);
	//Display Minutes
	LCD_Putc_xy( (pTimeArray[1]/10)+0x30, 3, 0 );
	LCD_Putc_xy( (pTimeArray[1]%10)+0x30, 4, 0 );
	LCD_Putrs(":", 5, 0);
    //Display Seconds
	LCD_Putc_xy( (pTimeArray[0]/10)+0x30, 6, 0 );
	LCD_Putc_xy( (pTimeArray[0]%10)+0x30, 7, 0 );
	LCD_Putrs(" ", 8, 0 );
    // Display mode
	switch(pTimeArray[3]){
        case AM_Time:   LCD_Putrs("AM", 9, 0);  break;
        case PM_Time:   LCD_Putrs("PM", 9, 0);  break;
        default:        LCD_Putrs('H', 9, 0);   break;
	}
}




void DisplayDateOnLCD( unsigned char* pDateArray ){   // Displays Date in DD:MM:YY @ Day format
	// Display Date
	LCD_Putc_xy( (pDateArray[1]/10)+0x30, 0, 1 );
	LCD_Putc_xy( (pDateArray[1]%10)+0x30, 1, 1 );
	LCD_Putrs("/", 2, 1);
    //Display Month
	LCD_Putc_xy( (pDateArray[2]/10)+0x30, 3, 1 );
	LCD_Putc_xy( (pDateArray[2]%10)+0x30, 4, 1 );
	LCD_Putrs("/", 5, 1);
	//Display Year
	LCD_Putc_xy( (pDateArray[3]/10)+0x30, 6, 1 );
	LCD_Putc_xy( (pDateArray[3]%10)+0x30, 7, 1 );
	LCD_Putrs(" ", 8, 1);
	// Display Day
	switch(pDateArray[0]){
        case Monday:	LCD_Putrs("MON", 9, 1);	break;
        case Tuesday:	LCD_Putrs("TUE", 9, 1);	break;
        case Wednesday:	LCD_Putrs("WED", 9, 1);	break;
        case Thursday:	LCD_Putrs("THU", 9, 1);	break;
        case Friday:	LCD_Putrs("FRI", 9, 1);	break;
        case Saturday:	LCD_Putrs("SAT", 9, 1);	break;
        case Sunday:	LCD_Putrs("SUN", 9, 1);	break;
        default:        LCD_Putrs("???", 9, 1);	break;
	}
}