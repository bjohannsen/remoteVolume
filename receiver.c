/*
 * receiver.c
 *
 * Wrapper for the IRMP libs.
 *
 * Author: dreimalb
 */
#include "receiver.h"

#ifndef F_CPU
#error F_CPU unkown
#endif

void receiver_init (void (*cb)(uint8_t))
{
	irmp_set_callback_ptr(cb); //callback for receive indicator

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

    irmp_init();
}

#ifdef TIM1_COMPA_vect                          // ATtiny84
#define COMPA_VECT  TIM1_COMPA_vect
#else
#define COMPA_VECT  TIMER1_COMPA_vect           // ATmega
#endif

ISR(COMPA_VECT)
{
  (void) irmp_ISR();
}

uint8_t is_repetition(IRMP_DATA irmp_data)
{
	return (irmp_data.flags & IRMP_FLAG_REPETITION);
}

uint8_t is_source_valid(IRMP_DATA irmp_data)
{
	return (irmp_data.address == SAMSUNG_ADDRESS);
}

uint8_t is_volume_up_command(IRMP_DATA irmp_data)
{
	return (irmp_data.command == SAMSUNG_CMD_VOL_PLUS);
}

uint8_t is_volume_down_command(IRMP_DATA irmp_data)
{
	return (irmp_data.command == SAMSUNG_CMD_VOL_MINUS);
}

uint8_t is_toggle_source_command(IRMP_DATA irmp_data)
{
	return (irmp_data.command == SAMSUNG_CMD_BACK || irmp_data.command == SAMSUNG_CMD_NEXT) && !is_repetition(irmp_data);
}

uint8_t is_toggle_subwoofer_command(IRMP_DATA irmp_data)
{
	return (irmp_data.command == SAMSUNG_CMD_PAUSE && !is_repetition(irmp_data));
}

uint8_t is_toggle_mute_command(IRMP_DATA irmp_data)
{
	return (irmp_data.command == SAMSUNG_CMD_MUTE && !is_repetition(irmp_data));
}

uint8_t receiver_get_command()
{
	IRMP_DATA irmp_data;
	if(irmp_get_data(&irmp_data) && is_source_valid(irmp_data))
	{
		if(is_volume_up_command(irmp_data))
		{
			return RECEIVER_COMMAND_VOLUME_UP;
		}
		else if(is_volume_down_command(irmp_data))
		{
			return RECEIVER_COMMAND_VOLUME_DOWN;
		}
		else if(is_toggle_mute_command(irmp_data))
		{
			return RECEIVER_COMMAND_TOGGLE_MUTE;
		}
		else if(is_toggle_subwoofer_command(irmp_data))
		{
			return RECEIVER_COMMAND_TOGGLE_SUBWOOFER;
		}
		else if(is_toggle_source_command(irmp_data))
		{
			return RECEIVER_COMMAND_TOGGLE_SOURCE;
		}
	}
	return RECEIVER_COMMAND_NONE;
}
