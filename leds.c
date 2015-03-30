/*
 * leds.c
 *
 *  Created on: 23.03.2014
 *      Author: BJO
 */
#include "leds.h"

uint8_t _leds_animations = 0x00;
uint8_t _leds_state = 0x0;
uint8_t _leds_highest = 0x0;
uint8_t _leds_mute_blink_counter = 0x0;
uint8_t _leds_rx_counter = 0x0;
uint8_t _leds_threshold_steps = 0x0;
uint16_t _leds_values = 0x0;
uint16_t _leds_adc_value = 0x0;

void leds_init(uint8_t gain_step_count)
{
	spi_init();
	adc_init();
	_leds_threshold_steps = (gain_step_count/LEDS_RANGE_COUNT);
}

uint8_t leds_get_highest()
{
	return _leds_highest;
}

uint8_t leds_get_threshold(uint8_t index)
{
	uint8_t i = LEDS_INDEX_MIN-index;
	return _leds_threshold_steps*i;
}

uint16_t leds_map_gain_values_and_states(uint8_t gain_level)
{
	uint16_t value = 0;
	uint8_t index = LEDS_INDEX_MIN;
	for(; index >= LEDS_INDEX_MAX; index--)
	{
		if(gain_level >= leds_get_threshold(index))
		{
			value |= (1<<index);
			_leds_highest = index-1;
		}
	}
	if(_leds_state & LEDS_STATE_SECOND_SOURCE)
	{
		value |= (1<<LEDS_INDEX_SOURCE);
	}

	if(_leds_state & LEDS_STATE_MUTED)
	{
		_leds_mute_blink_counter++;
		if(_leds_mute_blink_counter < LEDS_MUTED_BLINK_DELAY)
		{
			value |= (1<<LEDS_INDEX_MUTE | 1<<LEDS_INDEX_MUTE_2);
		}
		if(_leds_mute_blink_counter > (LEDS_MUTED_BLINK_DELAY<<1))
		{
			_leds_mute_blink_counter = 0;
		}
	}
	if(_leds_rx_counter) {
		if(_leds_rx_counter&0x01) {
			value ^= (1<<LEDS_INDEX_SOURCE);
		}
		_leds_rx_counter--;
	}
	return value;
}

void leds_set_animation(uint8_t animation)
{
	if(animation == LEDS_ANIMATION_MUTE)
	{
		_leds_mute_blink_counter = 0;
	}
	_leds_animations |= animation;
}

void leds_clear_values()
{
	uint8_t index = LEDS_INDEX_MIN;
	for(; index >= LEDS_INDEX_MAX; index--)
	{
		_leds_values &= ~(1<<index);
	}
}

void leds_animation_mute()
{
	static uint8_t index = LEDS_INDEX_MAX+1;

	//for(; index <= LEDS_INDEX_MAX; index++);

	uint8_t i = LEDS_INDEX_MIN;
	if(index <= LEDS_INDEX_MIN)
	{
		_leds_animations |= LEDS_ANIMATION_MUTED;
		for(; i >= index; i--)
		{
			if(_leds_adc_value & (1<<i))
			{
				_leds_values |= (1<<i);
			}
		}
		index++;
	}
	else
	{
		_leds_animations &= ~LEDS_ANIMATION_MUTE;
		index = LEDS_INDEX_MAX;
	}
}

void leds_animation_unmute()
{
	static uint8_t index = LEDS_INDEX_MIN;
	uint8_t i = LEDS_INDEX_MIN;
	if(index >= LEDS_INDEX_MAX)
	{
		leds_clear_values();
		_leds_animations &= ~LEDS_ANIMATION_MUTED;
		for(; i >= index; i--)
		{
			if(_leds_adc_value & (1<<i))
			{
				_leds_values |= (1<<i);
			}
		}
		index--;
	}
	else
	{
		_leds_animations &= ~LEDS_ANIMATION_UNMUTE;
		index = LEDS_INDEX_MIN;
	}
}

void leds_animation_vol_up()
{
	static uint8_t index = LEDS_INDEX_MIN;
	_leds_animations &= ~LEDS_ANIMATION_VOL_DOWN;
	if(index >= LEDS_INDEX_MAX)
	{
		_leds_values ^= (1<<index);
		index--;
	}
	else
	{
		index = LEDS_INDEX_MIN;
		_leds_animations &= ~LEDS_ANIMATION_VOL_UP;
	}
}

void leds_animation_vol_down()
{
	static uint8_t index = LEDS_INDEX_MAX;
	_leds_animations &= ~LEDS_ANIMATION_VOL_UP;
	if(index <= LEDS_INDEX_MIN)
	{
		_leds_values ^= (1<<index);
		index++;
	}
	else
	{
		index = LEDS_INDEX_MAX;
		_leds_animations &= ~LEDS_ANIMATION_VOL_DOWN;
	}
}

void leds_animation_muted()
{
	leds_clear_values();
}

void leds_rx()
{
	_leds_rx_counter = LEDS_RX_DELAY;
}

void leds_clear_second_source()
{
	_leds_state &= ~LEDS_STATE_SECOND_SOURCE;
}

void leds_set_second_source()
{
	_leds_state |= LEDS_STATE_SECOND_SOURCE;
}

void leds_set_state_muted()
{
	_leds_state |= LEDS_STATE_MUTED;
}

void leds_clear_state_muted()
{
	_leds_state &= ~LEDS_STATE_MUTED;
}

void leds_animate(uint8_t gain_level)
{
	_leds_adc_value = leds_map_gain_values_and_states(gain_level);
	_leds_values = _leds_adc_value;

	if(_leds_animations & LEDS_ANIMATION_MUTED)
	{
		leds_animation_muted();
	}
	if(_leds_animations & LEDS_ANIMATION_MUTE)
	{
		leds_animation_mute();
	}
	if(_leds_animations & LEDS_ANIMATION_UNMUTE)
	{
		leds_animation_unmute();
	}
	if(_leds_animations & LEDS_ANIMATION_VOL_UP)
	{
		leds_animation_vol_up();
	}
	if(_leds_animations & LEDS_ANIMATION_VOL_DOWN)
	{
		leds_animation_vol_down();
	}

	spi_write(_leds_values, LEDS_COUNT);
}
