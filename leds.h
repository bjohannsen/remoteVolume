/*
 * leds.h
 *
 * Author: dreimalb
 */
#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>
#include <stdio.h>
#include "spi.h"
#include "adc.h"

#define LEDS_COUNT 16
#define LEDS_INDEX_MAX 1
#define LEDS_INDEX_MIN 13
#define LEDS_RANGE_COUNT 13
#define LEDS_INDEX_SOURCE 15
#define LEDS_INDEX_MUTE 0
#define LEDS_INDEX_MUTE_2 14

#define LEDS_ANIMATION_MUTED 	0x01
#define LEDS_ANIMATION_UNMUTE 	0x02
#define LEDS_ANIMATION_MUTE 	0x04
#define LEDS_ANIMATION_VOL_UP	0x08
#define LEDS_ANIMATION_VOL_DOWN 0x10

#define LEDS_MUTED_BLINK_DELAY 	50
#define LEDS_RX_DELAY 7

#define LEDS_STATE_SECOND_SOURCE 0x01
#define LEDS_STATE_MUTED 0x02

void leds_init(uint8_t gain_step_count);
void leds_animate(uint8_t gain_level);
void leds_set_animation( uint8_t animation);
void leds_clear_second_source();
void leds_set_second_source();
void leds_set_state_muted();
void leds_clear_state_muted();
void leds_set_state_high_limit();
void leds_clear_state_high_limit();
void leds_rx();
uint8_t leds_get_highest();

#endif /* LEDS_H_ */
