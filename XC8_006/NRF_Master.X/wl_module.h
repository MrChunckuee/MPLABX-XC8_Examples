/*
        Modifications by Elia Ritterbusch
        http://eliaselectronics.com

        Copyright (c) 2011 by Ernst Buchmann

	Code based on the work of Stefan Engelke and Brennan Ball

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.


*/

#ifndef _WL_MODULE_H_
#define _WL_MODULE_H_

#include <xc.h>
#include "spi.h"

//Externe Variable deklarieren
extern volatile unsigned char PTX;

// WL-Module settings
#define wl_module_CH			2
#define wl_module_PAYLOAD		16
#define wl_module_RF_DR_HIGH	0		//0 = 1Mbps, 1 = 2Mpbs
#define wl_module_RF_SETUP		(RF_SETUP_RF_PWR_0 | RF_SETUP_RF_DR_250)
#define wl_module_CONFIG		( (1<<MASK_RX_DR) | (1<<EN_CRC) | (1<<CRCO) )
#define wl_module_TX_NR_0		0
#define wl_module_TX_NR_1		1
#define wl_module_TX_NR_2		2
#define wl_module_TX_NR_3		3
#define wl_module_TX_NR_4		4
#define wl_module_TX_NR_5		5

// Pin definitions for chip select and chip enabled of the wl-module
#define CE LATB3 // RB3
#define CSN LATB4 // RB4

// Definitions for selecting and enabling wl_module module
#define wl_module_CSN_hi     LATBbits.CSN = 1;
#define wl_module_CSN_lo     LATBbits.CSN = 0;
#define wl_module_CE_hi      LATBbits.CE = 1;
#define wl_module_CE_lo      LATBbits.CE = 0;

// Defines for setting the wl_module registers for transmitting or receiving mode
#define TX_POWERUP wl_module_config_register(CONFIG, wl_module_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )
#define RX_POWERUP wl_module_config_register(CONFIG, wl_module_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) )

// Public standard functions
extern void wl_module_init(void);
extern void wl_module_config(void);
extern void wl_module_send(unsigned char * value, unsigned char len);
extern void wl_module_set_RADDR(unsigned char * adr);
extern void wl_module_set_TADDR(unsigned char * adr);
extern unsigned char wl_module_data_ready(void);
//extern void wl_module_get_data(unsigned char * data);
extern unsigned char wl_module_get_data(unsigned char * data);			//Gibt die Werte des STATUS-Registers zurück

//Public functions

extern unsigned char wl_module_get_status(void);
extern unsigned char wl_module_get_rx_pipe_reading_status(void);
extern unsigned char wl_module_get_one_byte(unsigned char command);
extern void wl_module_set_rx_pw(unsigned char payloadwidth, unsigned char rxpipenum);
extern unsigned char wl_module_get_rx_pw(unsigned char rxpipenum);
extern void wl_module_set_tx_addr(unsigned char * address, unsigned char len);
extern void wl_module_set_rx_addr(unsigned char * address, unsigned char len, unsigned char rxpipenum);
extern void wl_module_tx_config(unsigned char tx_nr);
extern void wl_module_rx_config(void);
extern void wl_module_get_rx_addr(unsigned char * data, unsigned char rxpipenum, unsigned char len);
extern unsigned char wl_module_get_rx_pipe(void);
extern unsigned char wl_module_get_rx_pipe_from_status(unsigned char status);
extern unsigned char wl_module_fifo_tx_empty(void);	//returns true if TX_EMPTY bit in FIFO_STATUS register is set, false otherwise
extern unsigned char wl_module_fifo_rx_empty(void);
extern unsigned char wl_module_get_rf_ch(void);
extern unsigned char wl_module_get_rf_setup(void);
extern unsigned char wl_module_get_plos_cnt(void);
extern unsigned char wl_module_get_arc_cnt(void);
extern void wl_module_set_as_tx(void);			//activate module with existing config
extern void wl_module_power_down(void);			//powers down the module with existing config

// Public extended functions
extern void wl_module_config_register(unsigned char reg, unsigned char value);
extern void wl_module_read_register(unsigned char reg, unsigned char * value, unsigned char len);
extern void wl_module_write_register(unsigned char reg, unsigned char * value, unsigned char len);

#endif /* _SETUP_NRF24L01_H_ */
