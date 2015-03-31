#include "volumeRemote.h"

#ifndef F_CPU
#error F_CPU unkown
#endif

void timer1_init (void)
{
#if defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__)  // ATtiny45 / ATtiny85:

#if F_CPU >= 16000000L
    OCR1C   =  (F_CPU / F_INTERRUPTS / 8) - 1;            // compare value: 1/15000 of CPU frequency, presc = 8
    TCCR1   = (1 << CTC1) | (1 << CS12);                  // switch CTC Mode on, set prescaler to 8
#else
    OCR1C   =  (F_CPU / F_INTERRUPTS / 4) - 1;            // compare value: 1/15000 of CPU frequency, presc = 4
    TCCR1   = (1 << CTC1) | (1 << CS11) | (1 << CS10);    // switch CTC Mode on, set prescaler to 4
#endif

#else                                                     // ATmegaXX:
    OCR1A   =  (F_CPU / F_INTERRUPTS) - 1;                // compare value: 1/15000 of CPU frequency
    TCCR1B  = (1 << WGM12) | (1 << CS10);                 // switch CTC Mode on, set prescaler to 1
#endif

#ifdef TIMSK1
    TIMSK1  = 1 << OCIE1A;                      // OCIE1A: Interrupt by timer compare
#else
    TIMSK   = 1 << OCIE1A;                      // OCIE1A: Interrupt by timer compare
#endif
}

#ifdef TIM1_COMPA_vect                          // ATtiny84
#define COMPA_VECT  TIM1_COMPA_vect
#else
#define COMPA_VECT  TIMER1_COMPA_vect           // ATmega
#endif

// VolumeRemote Definitions
uint8_t _state = 0x0;
uint8_t _flags = 0x0;
uint8_t _submute_counter = 0;
uint8_t _gain_level = GAIN_STARTUP_STEP;


// IRMP Timer
// Timer1 output compare A interrupt service routine, called every 1/15000 sec
ISR(COMPA_VECT)
{
  (void) irmp_ISR();
}

//// Timer Interrupt
ISR(TIMER0_COMPA_vect)
{
	static uint8_t sw_timer=0;

	if(_submute_counter > 0)
	{
		_submute_counter--;
		if(_submute_counter==0) {
			RELAY_SUBMUTE_OPEN;
		}
	}

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
		RELAY_SOURCE_OPEN;
		leds_clear_second_source();
	}
	else
	{
		_state |= STATE_SECOND_SOURCE;
		RELAY_SOURCE_CLOSE;
		leds_set_second_source();
	}
}

void toggle_submute()
{
	RELAY_SUBMUTE_CLOSE;
	_submute_counter = RELAY_SUBMUTE_DELAY;
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

void init_io() {
    RELAY_DDR |= (RELAY_SOURCE|RELAY_SUBMUTE);
}

void init_volume_timer() {
	TCCR0A = (1<<WGM01);
	TCCR0B |= (1<<CS02|1<<CS00);
	OCR0A = 196;
	TIMSK0 |= (1<<OCIE0A);
}

uint8_t is_repetition(IRMP_DATA irmp_data)
{
	return irmp_data.flags & IRMP_FLAG_REPETITION;
}

int main (void)
{
    IRMP_DATA irmp_data;
    motor_init();
    init_io();
    init_volume_timer();
    pga_init();
    leds_init(GAIN_STEPS);
    irmp_init();
    timer1_init();
    irmp_set_callback_ptr(rx_led_callback);
    pga_unmute();

    sei ();
    update_pga_gain();

    for (;;)
    {
        if (irmp_get_data (&irmp_data))
        {
        	if(irmp_data.address == SAMSUNG_ADDRESS)
        	{
        		if((irmp_data.command == SAMSUNG_CMD_MUTE) && !is_repetition(irmp_data))
        		{
        			toggle_mute();
        		}
        		else if((irmp_data.command == SAMSUNG_CMD_PAUSE) && !is_repetition(irmp_data))
        		{
       				toggle_submute();
        		}
        		else if(irmp_data.command == SAMSUNG_CMD_BACK || irmp_data.command == SAMSUNG_CMD_NEXT)
        		{
        			if(!is_repetition(irmp_data))
        			{
        				toggle_source();
        			}
        		}
        		else if(irmp_data.command == SAMSUNG_CMD_VOL_PLUS)
        		{
        			turn_volume_up();
        		}
        		else if(irmp_data.command == SAMSUNG_CMD_VOL_MINUS)
        		{
        			turn_volume_down();
        		}
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
