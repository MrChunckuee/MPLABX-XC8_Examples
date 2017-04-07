/*
 *      2013 Elia Ritterbusch
 *      http://eliaselectronics.com
 *
 *      This work is licensed under the Creative Commons Attribution 3.0 Unported License.
 *      To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
 */
#ifndef _SPI_H_
#define	_SPI_H_

extern void spi_init(void);
extern void spi_transfer_sync(unsigned char* dataout, unsigned char* datain, unsigned int length);
extern void spi_transmit_sync(unsigned char* data, unsigned int length);
extern unsigned char spi_fast_shift(unsigned char data);

#endif	/* _SPI_H_ */

