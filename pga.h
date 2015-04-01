/*
 * pga.h
 *
 * Author: dreimalb
 */
#ifndef PGA_H_
#define PGA_H_

#include <avr/io.h>
#include <stdio.h>

// USER DEFINITIONS
#define GAIN_MIN			100		// -40dB //MAX: 192 (0xC0)
#define GAIN_BANDWIDTH		168		// number of steps (0.5db steps of pga)
#define GAIN_STEPWIDTH  	4   	// step width (in 0.5db)
#define GAIN_STARTUP_STEP 	10
// END OF USER DEFINTIONS

#define PGA_GAIN_MUTE 0
#define PGA_GAIN_MAX 255

#define PGA_MUTE_PIN		(1<<PORTD5)
#define PGA_UNMUTE 			(PGA_SPI_PORT |= PGA_MUTE_PIN)
#define PGA_MUTE 			(PGA_SPI_PORT &= ~(PGA_MUTE_PIN))

#define PGA_SPI_PORT 		PORTD
#define PGA_SPI_DDR			DDRD
#define PGA_SPI_PIN_CS		(1<<PORTD4)
#define PGA_SPI_PIN_SCK		(1<<PORTD6)
#define PGA_SPI_PIN_SER		(1<<PORTD7)

#define PGA_SPI_SET_CS		(PGA_SPI_PORT |= PGA_SPI_PIN_CS)
#define PGA_SPI_CLR_CS		(PGA_SPI_PORT &= ~(PGA_SPI_PIN_CS))
#define PGA_SPI_SET_SER		(PGA_SPI_PORT |= PGA_SPI_PIN_SER)
#define PGA_SPI_CLR_SER		(PGA_SPI_PORT &= ~(PGA_SPI_PIN_SER))
#define PGA_SPI_SET_SCK		(PGA_SPI_PORT |= PGA_SPI_PIN_SCK)
#define PGA_SPI_CLR_SCK		(PGA_SPI_PORT &= ~(PGA_SPI_PIN_SCK))

#define PGA_SPI_INIT_SER_PIN (PGA_SPI_DDR |= PGA_SPI_PIN_SER)
#define PGA_SPI_INIT_SCK_PIN (PGA_SPI_DDR |= PGA_SPI_PIN_SCK)
#define PGA_SPI_INIT_CS_PIN  (PGA_SPI_DDR |= PGA_SPI_PIN_CS)

#define GAIN_STEPS			(GAIN_BANDWIDTH/GAIN_STEPWIDTH)
#define GAIN_MAX 			(GAIN_MIN+(GAIN_STEPS*GAIN_STEPWIDTH))

void pga_init();
void pga_set_gain(uint8_t gain);
uint8_t pga_get_gain_for_level(uint8_t level);
void pga_mute();
void pga_unmute();

#endif /* PGA_H_ */
