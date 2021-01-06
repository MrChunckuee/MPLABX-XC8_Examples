/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F25K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED_Status_RC6 aliases
#define LED_Status_RC6_TRIS                 TRISCbits.TRISC6
#define LED_Status_RC6_LAT                  LATCbits.LATC6
#define LED_Status_RC6_PORT                 PORTCbits.RC6
#define LED_Status_RC6_ANS                  ANSELCbits.ANSC6
#define LED_Status_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_Status_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_Status_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_Status_RC6_GetValue()           PORTCbits.RC6
#define LED_Status_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_Status_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_Status_RC6_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_Status_RC6_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set LED_Status_RC7 aliases
#define LED_Status_RC7_TRIS                 TRISCbits.TRISC7
#define LED_Status_RC7_LAT                  LATCbits.LATC7
#define LED_Status_RC7_PORT                 PORTCbits.RC7
#define LED_Status_RC7_ANS                  ANSELCbits.ANSC7
#define LED_Status_RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define LED_Status_RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define LED_Status_RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define LED_Status_RC7_GetValue()           PORTCbits.RC7
#define LED_Status_RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define LED_Status_RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define LED_Status_RC7_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define LED_Status_RC7_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/