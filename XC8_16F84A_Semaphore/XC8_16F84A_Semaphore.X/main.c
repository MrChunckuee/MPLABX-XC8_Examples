/*******************************************************************************
 *
 *                  Semaforo basico
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC16F84A
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Simular con LEDs un par de semaforos, utilizando un ya muy 
 *                  conocido microcontrolador.
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      05/06/2017      Creación del ejemplo
 ******************************************************************************/
#include <xc.h>

// PIC16F84A Configuration Bit Settings
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (Power-up Timer is enabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

//Definimos la velocidad de 4MHz
#define _XTAL_FREQ  4000000

//Etiquetas para las salidas
//Renombramos los pines para que sea mas facil acceder a ellos
#define LEDA_Verde      PORTBbits.RB0 //
#define LEDA_Amarillo   PORTBbits.RB1 // Semaforo 1
#define LEDA_Rojo       PORTBbits.RB2 // 
#define LEDB_Verde      PORTBbits.RB3 // 
#define LEDB_Amarillo   PORTBbits.RB4 // Semaforo 2
#define LEDB_Rojo       PORTBbits.RB5 // 

//Etiquetas globales, para hacer el codigo mas comprensible
#define Encender    1
#define Apagar      0
#define AllOutput   0x00
#define AllClear    0x00

//Variables generales
unsigned char count;

//Declaracion de prototipos
void MCU_Delayms(unsigned int t);

//Funcion principal
void main(void) {
    //Inicializamos PIC
    TRISB = AllOutput; //Puerto B como salida
    PORTB = AllClear; //Limpiamos puerto B
    while(1){//Inicia la secuancia de semaforo
        LEDA_Verde = Encender;//Encendemos LED verde del semaforo 1
        LEDB_Rojo = Encender;//Encendemos LED rojo de semaforo 2
        MCU_Delayms(9000); //Retardo de 9 segundos
        LEDA_Verde = Apagar;//Apagamos LED verde del semaforo 1
        //Hacemos que LED amarillo del semaforo 1 este intermitente
        for(count=0; count<10; count++){//Esto hace que el LED amarillo del
            LEDA_Amarillo ^= 1;         //primer semaforo este de una forma
            MCU_Delayms(300);           //intermitente cada 0.3 segundos 
        }                               //por 10 veces
        LEDB_Rojo = Apagar;//Apagamos LED rojo del semaforo 2
        LEDB_Verde = Encender;//Encendemos LED verde del semaforo 1
        LEDA_Rojo = Encender;//Encendemos LED rojo de semaforo 1
        MCU_Delayms(9000);//Retardo de 9 segundos
        LEDB_Verde = Apagar;//Apagamos LED verde del semaforo 2
        //Hacemos que LED amarillo del semaforo 2 este intermitente
        for(count=0; count<10; count++){//Esto hace que el LED amarillo del
            LEDB_Amarillo ^= 1;         //segundo semaforo este de una forma
            MCU_Delayms(300);           //intermitente cada 0.3 segundos
        }                               //por 10 veces
        LEDA_Rojo = Apagar;//Apagamos LED rojo del semaforo 1     
    }//Termina la secuencia del semaforo.
     //pero se vuleve a repetir indeterminadamente
}

//Rutina para generar retardos en milisegundos
void MCU_Delayms(unsigned int t){
    unsigned int acc;
    //Se repite mientras acc sea menos a t
    for(acc=0; acc<t; acc++){
        __delay_ms(1); //Retardo de 1 milisegundo
    }
}
