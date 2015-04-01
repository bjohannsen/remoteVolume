/*
 * relay.c
 *
 * Wrapper to handle subwoofer mute and source relays.
 *
 * Author: @dreimalbe
 */
#include "relays.h"

uint8_t _relays_latch_delay = 0;

void relays_init()
{
    RELAY_DDR |= (RELAY_SOURCE|RELAY_SUBMUTE);
}

void relays_handle_latches()
{
	if(_relays_latch_delay > 0)
	{
		_relays_latch_delay--;
		if(_relays_latch_delay==0) {
			RELAY_SUBWOOFER_MUTE_OPEN;
		}
	}
}

void relays_toggle_subwoofer()
{
	_relays_latch_delay = RELAY_SUBWOOFER_MUTE_DELAY;
	RELAY_SUBWOOFER_MUTE_CLOSE;
}

void relays_set_second_source()
{
	RELAY_SOURCE_CLOSE;
}

void relays_set_main_source()
{
	RELAY_SOURCE_OPEN;
}

