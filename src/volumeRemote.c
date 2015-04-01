/*
 * volumeRemote.c
 *
 * Main file of VolumeRemote project.
 *
 * Author: @dreimalbe
 */
#include "volumeRemote.h"

uint8_t _state = 0x0;
uint8_t _flags = 0x0;
uint8_t _gain_level = GAIN_STARTUP_STEP;

// Timer Interrupt
ISR(TIMER0_COMPA_vect)
{
	static uint8_t sw_timer=0;

	relays_handle_latches();

	if(sw_timer&0x01)
	{
		_flags |= FLAG_LED_ANIMATION;
	}
	sw_timer++;

	_flags |= FLAG_CHECK_MOTOR_POSTION;
}

void update_pga_gain()
{
	pga_set_gain(pga_get_gain_for_level(_gain_level));
}

void toggle_mute()
{
	if(_state & STATE_MUTE)
	{
		_state &= ~STATE_MUTE;
		pga_unmute();
		leds_clear_state_muted();
		leds_set_animation(LEDS_ANIMATION_UNMUTE);
	}
	else
	{
		_state |= STATE_MUTE;
		pga_mute();
		leds_set_state_muted();
		leds_set_animation(LEDS_ANIMATION_MUTE);
	}
}

void toggle_source()
{
	if(_state & STATE_SECOND_SOURCE)
	{
		_state &= ~STATE_SECOND_SOURCE;
		relays_set_main_source();
		leds_clear_second_source();
	}
	else
	{
		_state |= STATE_SECOND_SOURCE;
		relays_set_second_source();
		leds_set_second_source();
	}
}

void turn_volume_up()
{
	if(_gain_level < GAIN_STEPS)
	{
		_gain_level++;
		update_pga_gain();
		leds_set_animation(LEDS_ANIMATION_VOL_UP);
		_flags |= FLAG_CALC_MOTOR_TARGET;
	}
}

void turn_volume_down()
{
	if(_gain_level > 0)
	{
		_gain_level--;
		update_pga_gain();
		leds_set_animation(LEDS_ANIMATION_VOL_DOWN);
		_flags |= FLAG_CALC_MOTOR_TARGET;
	}
}

void rx_led_callback(uint8_t on)
{
	leds_rx();
}

void init_volume_timer()
{
	TCCR0A = (1<<WGM01);
	TCCR0B |= (1<<CS02|1<<CS00);
	OCR0A = 196;
	TIMSK0 |= (1<<OCIE0A);
}

int main (void)
{
    init_volume_timer();

    motor_init();
    relays_init();
    pga_init();
    leds_init(GAIN_STEPS);
    receiver_init(rx_led_callback);

    update_pga_gain();
    pga_unmute();
    motor_update_target(_gain_level);

    sei();

    for(;;)
    {
    	uint8_t command = receiver_get_command();
        if(command)
        {
        	if(command == RECEIVER_COMMAND_VOLUME_UP)
        	{
        		turn_volume_up();
        	}
        	else if(command == RECEIVER_COMMAND_VOLUME_DOWN)
        	{
        		turn_volume_down();
        	}
        	else if(command == RECEIVER_COMMAND_TOGGLE_MUTE)
        	{
        		toggle_mute();
        	}
        	else if(command == RECEIVER_COMMAND_TOGGLE_SUBWOOFER)
        	{
        		relays_toggle_subwoofer();
        	}
        	else if(command == RECEIVER_COMMAND_TOGGLE_SOURCE)
        	{
        		toggle_source();
        	}
        }

        if(_flags & FLAG_CALC_MOTOR_TARGET)
        {
        	motor_update_target(_gain_level);
        	_flags &= ~FLAG_CALC_MOTOR_TARGET;
        }
        else if(_flags & FLAG_LED_ANIMATION)
        {
    		leds_animate(_gain_level);
        	_flags &= ~FLAG_LED_ANIMATION;
        }
        else if(_flags & FLAG_CHECK_MOTOR_POSTION)
        {
        	motor_check_position(adc_get_value(0));
        	_flags &= ~FLAG_CHECK_MOTOR_POSTION;
        }
    }
}
