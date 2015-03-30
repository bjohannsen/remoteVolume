/*
 * volumeRemote.h
 *
 *  Created on: 27.01.2014
 *      Author: BJO
 */

#ifndef VOLUMEREMOTE_H_
#define VOLUMEREMOTE_H_
#include <math.h>
#include "irmp.h"
#include "leds.h"
#include "adc.h"
#include "pga.h"

#define SAMSUNG_CMD_MUTE 		0xF00F
#define SAMSUNG_CMD_VOL_PLUS	0xF807
#define SAMSUNG_CMD_VOL_MINUS	0xF40B
#define SAMSUNG_CMD_A			0x936C
#define SAMSUNG_CMD_B			0xEB14
#define SAMSUNG_CMD_C			0xEA15
#define SAMSUNG_CMD_D			0xE916
#define SAMSUNG_CMD_PAUSE		0xB54A
#define SAMSUNG_CMD_BACK		0xBA45
#define SAMSUNG_CMD_NEXT		0xB748
#define SAMSUNG_CMD_PLAY		0xB847
#define SAMSUNG_CMD_STOP		0xB946

#define SAMSUNG_ADDRESS			0x0707

// States
#define STATE_MUTE				0x01
#define STATE_SUB_BYPASS		0x02
#define STATE_SECOND_SOURCE		0x04

// Flags
#define FLAG_CALC_MOTOR_TARGET	0x01
#define FLAG_LED_ANIMATION		0x02

// Befehle ///////////////////////////////////////
#define MOTOR_PORT				PORTD
#define MOTOR_DDR				DDRD
#define MOTOR_B					(1<<PORTD0)
#define MOTOR_A					(1<<PORTD1)

#define RELAY_PORT				PORTD
#define RELAY_DDR				DDRD
#define RELAY_SUBMUTE			(1<<PORTD3)
#define RELAY_SOURCE			(1<<PORTD2)

#define RELAY_SUBMUTE_DELAY		25

#define MOTOR_STOP				(MOTOR_PORT &= ~( MOTOR_A | MOTOR_B ) )
#define MOTOR_RUN_CW			(MOTOR_PORT |= MOTOR_A )
#define MOTOR_RUN_CCW			(MOTOR_PORT |= MOTOR_B )

#define RELAY_SUBMUTE_CLOSE		(RELAY_PORT |= RELAY_SUBMUTE)
#define RELAY_SUBMUTE_OPEN		(RELAY_PORT &= ~(RELAY_SUBMUTE))
#define RELAY_SOURCE_CLOSE		(RELAY_PORT |= RELAY_SOURCE)
#define RELAY_SOURCE_OPEN		(RELAY_PORT &= ~(RELAY_SOURCE))

#define ADC_TOLERANCE 0.1

#endif /* VOLUMEREMOTE_H_ */
