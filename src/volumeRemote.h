/*
 * volumeRemote.h
 *
 * Author: @dreimalbe
 */
#ifndef VOLUMEREMOTE_H_
#define VOLUMEREMOTE_H_

#include "receiver.h"
#include "adc.h"
#include "motorpot.h"
#include "leds.h"
#include "pga.h"
#include "relays.h"

// States
#define STATE_MUTE					0x01
#define STATE_SUB_BYPASS			0x02
#define STATE_SECOND_SOURCE			0x04

// Flags
#define FLAG_CALC_MOTOR_TARGET		0x01
#define FLAG_LED_ANIMATION			0x02
#define FLAG_CHECK_MOTOR_POSTION 	0x04

#define SECOND_SOURCE_INPUT_GAIN	4	// number of level steps to add for this source.

#endif /* VOLUMEREMOTE_H_ */
