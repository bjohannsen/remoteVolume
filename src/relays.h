/*
 * relay.h
 *
 * Author: @dreimalbe
 */
#ifndef RELAYS_H_
#define RELAYS_H_

#include <avr/io.h>
#include <stdio.h>

#define RELAY_PORT					PORTD
#define RELAY_DDR					DDRD
#define RELAY_SUBMUTE				(1<<PORTD3)
#define RELAY_SOURCE				(1<<PORTD2)

#define RELAY_SUBWOOFER_MUTE_DELAY	25

#define RELAY_SUBWOOFER_MUTE_CLOSE	(RELAY_PORT |= RELAY_SUBMUTE)
#define RELAY_SUBWOOFER_MUTE_OPEN	(RELAY_PORT &= ~(RELAY_SUBMUTE))
#define RELAY_SOURCE_CLOSE			(RELAY_PORT |= RELAY_SOURCE)
#define RELAY_SOURCE_OPEN			(RELAY_PORT &= ~(RELAY_SOURCE))

void relays_handle_latches();
void relays_init();
void relays_toggle_subwoofer();
void relays_set_second_source();
void relays_set_main_source();

#endif /* RELAYS_H_ */
