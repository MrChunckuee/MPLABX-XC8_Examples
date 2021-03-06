/* 
 * File:   i2c.h
 * Author: mrchu_000
 *
 * Created on 19 de julio de 2017, 11:27 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

// Define i2c pins
#define SDA			RC4				// Data pin for i2c
#define SCK			RC3				// Clock pin for i2c
#define SDA_DIR		TRISC4			// Data pin direction
#define SCK_DIR		TRISC3			// Clock pin direction

// Define i2c speed
#define I2C_SPEED	100				// kbps

//Function Declarations
void InitI2C(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
bit  I2C_Write_Byte(unsigned char);
unsigned char I2C_Read_Byte(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

