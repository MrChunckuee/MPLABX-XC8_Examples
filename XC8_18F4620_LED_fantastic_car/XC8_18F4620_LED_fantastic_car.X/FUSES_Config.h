/* 
 * File:   FUSES_Config.h
 * Author: MRCHUNCKUEE
 *
 * Created on 2 de enero de 2019, 08:24 PM
 */

#ifndef FUSES_CONFIG_H
#define	FUSES_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

// Configuracion del PIC18F4620
#pragma config OSC = INTIO67    //Uso del osc interno
#pragma config FCMEN = ON
#pragma config IESO = ON
#pragma config PWRT = ON
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON       //Se activa el reset externo
#pragma config LVP = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF 
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT3 = OFF 
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
    
#ifdef	__cplusplus
}
#endif

#endif	/* FUSES_CONFIG_H */

