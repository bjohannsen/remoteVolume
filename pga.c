/*
 * pga.c
 *
 * Controller for the PGA2311 audio ic.
 *
 * Author: dreimalb
 */
#include "pga.h"

void pga_spi_write(uint16_t data)
{
	PGA_SPI_CLR_CS; //low active!
	uint16_t mask = 0x8000;
	while(mask > 0)
	{
		if(data & mask)
		{
			PGA_SPI_SET_SER;
		}
		else
		{
			PGA_SPI_CLR_SER;
		}
		PGA_SPI_SET_SCK;
		asm("nop");
		PGA_SPI_CLR_SCK;
		mask = mask>>1;
	}
	PGA_SPI_SET_CS;
}

void pga_spi_init() {
	PGA_SPI_INIT_CS_PIN;
	PGA_SPI_INIT_SCK_PIN;
	PGA_SPI_INIT_SER_PIN;
}

void pga_set_gain(uint8_t gain)
{
	uint16_t pga_gain = gain;
	pga_gain = pga_gain << 8;
	pga_gain = pga_gain + (uint16_t)gain;
	pga_spi_write(pga_gain);
}

uint8_t pga_get_gain_for_level(uint8_t level)
{
	return GAIN_MIN + level*GAIN_STEPWIDTH;
}

void pga_mute()
{
	PGA_MUTE;
}

void pga_unmute()
{
	PGA_UNMUTE;
}

void pga_init()
{
	PGA_SPI_DDR |= PGA_MUTE_PIN;
	pga_spi_init();
}
