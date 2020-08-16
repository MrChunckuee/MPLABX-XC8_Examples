/*******************************************************************************
 *
 *          PWM por software - Controlando tiras de LEDs RGB
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v1.42 & MPLAB X IDE v5.35
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Gererar tres señales de PWM por medio de la interrupcion del 
 *                  timer 0, esto para controlar una tira de LEDs RGB
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.0     08/08/2018      - Creación del ejemplo
 ******************************************************************************/

#include <xc.h>
#include "hw_sw.h"
#include "FUSES_Config.h"

unsigned int Ticks = 0;
unsigned char DuttyPWM[4]; // Red, Green, Blue
unsigned char levelColor;
unsigned int ticksRGB = 0;
unsigned char color = 0;

unsigned char colors[NUMBER_OF_COLORS][3] = {
    {255, 0,   0},  //Rojo
    {139, 0,   0},  
    {255, 127, 0},  //Naranja
    {255, 255, 0},  //Amarillo
    {0,   255, 0},  //Verde
    {0,   0,   255},//Azul
    {0,   255, 255},//Cyan
    {127, 255, 212},
    {75,  0,   130},//Morado    
    {143, 0,   255},
    {255, 255, 255}, //Blanco
};

void MCU_Init(void);
void PWM_Init(void);
void PWM_SetDutty(unsigned char Red, unsigned char Green, unsigned char Blue);
void demoRGBColor(void);

void interrupt high_priority ISR(void){
    if(INTCONbits.TMR0IF){
        
        if (Ticks == 256) Ticks = 0;
        ++Ticks;
        
        if (Ticks < DuttyPWM[ticksRed]) redLedOutput = 1;
        else redLedOutput = 0;
        
        if (Ticks < DuttyPWM[ticksGreen]) greenLedOutput = 1;
        else greenLedOutput = 0;
        
        if (Ticks < DuttyPWM[ticksBlue]) blueLedOutput = 1;
        else blueLedOutput = 0;
        
        TMR0H = 0x00;
        TMR0L = 0xB2;
        INTCONbits.TMR0IF = 0;
    }
}

void main(void) {
    MCU_Init();
    while(1){
        demoRGBColor();
    }
}

void MCU_Init(void){
    //Puertos digitales
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    //Configura oscilador interno a 16MHz
    OSCCONbits.IRCF=0b111; //El ciclo de instruccion es de 0.25 us
    //Puertos como salida
    TRISB = 0x00;
    TRISC = 0x00;
    //Limpiamos puertos
    PORTB = 0x00;
    PORTC = 0x00;
    
    DuttyPWM[ticksRed]      = 0;
    DuttyPWM[ticksGreen]    = 0;
    DuttyPWM[ticksBlue]     = 0;
    
    PWM_Init();
}

void PWM_Init(void){
    //Configuración del TMR0 = 39us
    T0CONbits.TMR0ON = 1; //TMR0 On
    T0CONbits.T08BIT = 1; //8 bits
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b000; // Prescaler = 2
    TMR0H = 0x00;
    TMR0L = 0xB2;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCON2bits.TMR0IP = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
}

void PWM_SetDutty(unsigned char Red, unsigned char Green, unsigned char Blue){
    //Set PWM dutty cycle
    DuttyPWM[ticksRed] = Red;
    DuttyPWM[ticksGreen] = Green;
    DuttyPWM[ticksBlue] = Blue;
}

void demoRGBColor(void){
    switch (color){
        case 0: // Fade Red
            ++ticksRGB;
            if (ticksRGB == 256) {
                color = 1;
                ticksRGB = 0;
            }
            PWM_SetDutty(ticksRGB,0,0);
            break;
        case 1: //Fade Green
            ++ticksRGB;
            if (ticksRGB == 256) {
                color = 2;
                ticksRGB = 0;
            }
            PWM_SetDutty(0,ticksRGB,0);
            break;
        case 2: //Fade Blue
            ++ticksRGB;
            if (ticksRGB == 256) {
                color = 3;
                ticksRGB = 0;
            }
            PWM_SetDutty(0,0,ticksRGB);
            break;
        case 3: //Show colors 
            for(levelColor=0; levelColor<NUMBER_OF_COLORS; levelColor++){
                PWM_SetDutty(colors[levelColor][0], colors[levelColor][1], colors[levelColor][2]);
                __delay_ms(1000);
            }
            color=0;
            break;
        default:
            color = 0;
            ticksRGB = 0;
            break;
    }
    __delay_ms(30);
}