/*
 * spi.h
 *
 * Author: dreimalb
 */
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdio.h>

#define SPI_PORT 		PORTC
#define SPI_DDR			DDRC

#define SPI_PIN_SCL		(1<<PORTC2)
#define SPI_PIN_SCK		(1<<PORTC3)
#define SPI_PIN_RCK		(1<<PORTC4)
#define SPI_PIN_SER		(1<<PORTC5)

#define SPI_SET_SER		(SPI_PORT |= SPI_PIN_SER)
#define SPI_CLR_SER		(SPI_PORT &= ~(SPI_PIN_SER))
#define SPI_SET_RCK		(SPI_PORT |= SPI_PIN_RCK)
#define SPI_CLR_RCK		(SPI_PORT &= ~(SPI_PIN_RCK))
#define SPI_SET_SCK		(SPI_PORT |= SPI_PIN_SCK)
#define SPI_CLR_SCK		(SPI_PORT &= ~(SPI_PIN_SCK))
#define SPI_SET_SCL		(SPI_PORT |= SPI_PIN_SCL)
#define SPI_CLR_SCL		(SPI_PORT &= ~(SPI_PIN_SCL))

#define SPI_INIT_SER_PIN (SPI_DDR |= SPI_PIN_SER)
#define SPI_INIT_RCK_PIN (SPI_DDR |= SPI_PIN_RCK)
#define SPI_INIT_SCK_PIN (SPI_DDR |= SPI_PIN_SCK)
#define SPI_INIT_SCL_PIN (SPI_DDR |= SPI_PIN_SCL)

void spi_write( uint16_t data, uint8_t size );
void spi_init();

#endif /* SPI_H_ */
