/*******************************************************************************
 *
 *                  XC8_002: LEDs con efecto auto fantastico 
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC12F675
 * Complier:        XC8 v1.30
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Lueces con efecto del auto fantatico usando el resgistro
 *                  de desplazamiento 74HC595. MCLR On, INT OSC = 4MHz
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      07/11/2015      Creación del firmware
 ******************************************************************************/

#include <xc.h>
#include <pic12f675.h>

//Configuracion de FUSES del PIC12F675
#pragma config FOSC=INTRCIO //Int OSC = 4MHz
#pragma config WDTE=OFF     //Disables Watchdog Timer
#pragma config PWRTE=OFF    //Disable Power-Up Timer
#pragma config MCLRE=ON     //Enable Master Clear
#pragma config BOREN=OFF    //Disable Blown-ou Detect
#pragma config CP=OFF       //Disable Code Protection
#pragma config CPD=OFF      //Disable Data Code Protection

#define _XTAL_FREQ  4000000
#define pinSH_CLK   GPIObits.GP1
#define pinDATA     GPIObits.GP2
#define pinST_CLK   GPIObits.GP4

//Variable conde almacenamos los datos a mostar
unsigned char LEDs_DATA[7]={0b10000001,
                            0b01000010,
                            0b00100100,
                            0b00011000,
                            0b00100100,
                            0b01000010,
                            0b10000001};

//Declaracion de funciones utilizadas
void MCU_Init(void);
void Send_Data(unsigned char DATA);
void Delay_ms(unsigned int t);

void main (void){
    unsigned char i;
    MCU_Init(); //Inicializamos uC
    while(1){
        for(i=0; i<6; i++){
            Send_Data(LEDs_DATA[i]); //Mostramos un dato de 8bits a la vez
            Delay_ms(250); //Pausa entre envio de datos
        }
    }
}

void MCU_Init(void){
    ANSELbits.ANS = 0b0000;   //Entradas y salidas digitales
    CMCONbits.CM = 0b111;     //Deactivamos comparadores
    TRISIO = 0x00;             //GP0 como salida, en realidad todo el puerto
    //Limpiamos pines antes de usarlos
    pinSH_CLK = 0;
    pinDATA   = 0;
    pinST_CLK = 0;
}

//Esta funcion evia los datos al 74HC595
void Send_Data(unsigned char DATA){
    unsigned char LOOP, FLAG;
    for (LOOP=0; LOOP<8; LOOP++){
        FLAG=DATA&0x01;
        if(FLAG==0) pinDATA=0;
        else pinDATA=1;
        pinSH_CLK = 1;
        pinSH_CLK = 0;
        DATA >>= 1;
        }
    pinST_CLK = 1;
    pinST_CLK = 0;
}

//Delay en milisegundos t = tiempo del delay
void Delay_ms(unsigned int t){
    unsigned int j;
    for(j=0;j<t;j++){
        __delay_ms(1);
    }
}

