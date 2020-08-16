/*******************************************************************************
 *
 *                  Uso del ADC: LEDs + pontenciometro
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC12F675
 * Complier:        XC8 v1.42
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Lueces con efecto del auto fantatico usando el resgistro
 *                  de desplazamiento 74HC595, la velocidad del efecto varia
 *                  con el potenciometro de 10K conectado en AN0.
 *                  MCLR On, INT OSC = 4MHz
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
#pragma config MCLRE=ON    //Enable Master Clear
#pragma config BOREN=OFF    //Disable Blown-ou Detect
#pragma config CP=OFF       //Disable Code Protection
#pragma config CPD=OFF      //Disable Data Code Protection

#define _XTAL_FREQ  4000000
#define pinADC_POT  GPIObits.GP0
#define pinSH_CLK   GPIObits.GP1
#define pinDATA     GPIObits.GP2
#define pinST_CLK   GPIObits.GP4

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
void ADC_Init(void);
unsigned int ADC_Read(void);
void Delay_ms(unsigned int t);

void main (void){
    unsigned char i;
    MCU_Init();
    while(1){
        for(i=0; i<6; i++){
            Send_Data(LEDs_DATA[i]);
            Delay_ms(ADC_Read());
        }
    }
}

void MCU_Init(void){
    ADC_Init(); //Configura e inicializa el ADC
    TRISIO = 0b000001; //Solo AN0 como entrada lo demas es salida
    //Limpiamos los pines antes de usarlos
    pinADC_POT = 0;
    pinSH_CLK  = 0;
    pinDATA    = 0;
    pinST_CLK  = 0;
}

void Send_Data(unsigned char DATA){
    unsigned char LOOP, FLAG;
    for (LOOP=0; LOOP<8; LOOP++){
        FLAG = DATA & 0x01;
        if(FLAG==0) pinDATA=0;
        else pinDATA=1;
        pinSH_CLK = 1;
        pinSH_CLK = 0;
        DATA >>= 1;
        }
    pinST_CLK = 1;
    pinST_CLK = 0;
}

void ADC_Init(void){
    //Configuracion del ADC
    ADCON0bits.ADFM = 1;
    ADCON0bits.VCFG = 0;//Voltage Reference VDD
    ADCON0bits.CHS  = 0b00; //Select chanel AN0
    ANSELbits.ADCS  = 0b100;
    ANSELbits.ANS   = 0b0001;
    ADCON0bits.ADON = 1;//Turn ADC on
}

unsigned int ADC_Read(void){
    int RESULT_ADC = 0;
    ADCON0bits.GO = 1;//Start ADC
    while(ADCON0bits.GO);
        RESULT_ADC = ADRESH << 8;
        RESULT_ADC = RESULT_ADC + ADRESL;
    return (RESULT_ADC);//Return ADC value
}

void Delay_ms(unsigned int t){
    //Delay t times in ms
    unsigned int j;
    for(j=0;j<t;j++){
        __delay_ms(1);
    }
}

