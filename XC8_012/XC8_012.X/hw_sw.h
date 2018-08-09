/* 
 * File:   hw_sw.h
 * Author: MrChunckuee
 *
 * Created on 8 de agosto de 2018, 11:41 PM
 */

#ifndef HW_SW_H
#define	HW_SW_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <pic18f25k22.h>
    
#define _XTAL_FREQ  16000000

/*********** P O R T   D E F I N I T I O N S **********************************/
#define redLedOutput    PORTBbits.RB0
#define greenLedOutput  PORTBbits.RB1
#define blueLedOutput   PORTBbits.RB2
    
#define ticksRed     0
#define ticksGreen   1
#define ticksBlue    2

#define NUMBER_OF_COLORS 11

#ifdef	__cplusplus
}
#endif

#endif	/* HW_SW_H */

