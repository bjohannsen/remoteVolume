/*
 * spi.c
 *
 *  Created on: 23.03.2014
 *      Author: BJO
 */
#include "spi.h"

void spi_write(uint16_t data, uint8_t size)
{
	uint8_t i = 0;
	SPI_SET_SCL;

	for(i=0; i < size; i++)
	{
		if((data & (1<<i)))
		{
			SPI_SET_SER;
		}
		else
		{
			SPI_CLR_SER;
		}
		SPI_SET_SCK;
		asm("nop");
		SPI_CLR_SCK;
	}
	SPI_SET_RCK;
	asm("nop");
	SPI_CLR_RCK;
}

void spi_init()
{
	SPI_INIT_RCK_PIN;
	SPI_INIT_SCK_PIN;
	SPI_INIT_SER_PIN;
	SPI_INIT_SCL_PIN;
}

