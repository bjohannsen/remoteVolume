#ifndef VOLUMEREMOTE_H_
#define VOLUMEREMOTE_H_

#include "irmp.h"
#include "receiver.h"
#include "adc.h"
#include "motorpot.h"
#include "leds.h"
#include "pga.h"

// States
#define STATE_MUTE					0x01
#define STATE_SUB_BYPASS			0x02
#define STATE_SECOND_SOURCE			0x04

// Flags
#define FLAG_CALC_MOTOR_TARGET		0x01
#define FLAG_LED_ANIMATION			0x02
#define FLAG_CHECK_MOTOR_POSTION 	0x04

#define RELAY_PORT				PORTD
#define RELAY_DDR				DDRD
#define RELAY_SUBMUTE			(1<<PORTD3)
#define RELAY_SOURCE			(1<<PORTD2)

#define RELAY_SUBMUTE_DELAY		25

#define RELAY_SUBMUTE_CLOSE		(RELAY_PORT |= RELAY_SUBMUTE)
#define RELAY_SUBMUTE_OPEN		(RELAY_PORT &= ~(RELAY_SUBMUTE))
#define RELAY_SOURCE_CLOSE		(RELAY_PORT |= RELAY_SOURCE)
#define RELAY_SOURCE_OPEN		(RELAY_PORT &= ~(RELAY_SOURCE))

#endif /* VOLUMEREMOTE_H_ */
