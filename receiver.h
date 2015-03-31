/*
 * receiver.c
 *
 * Author: dreimalb
 */
#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "irmp.h"

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

#define RECEIVER_COMMAND_NONE				0x00
#define RECEIVER_COMMAND_VOLUME_UP			0x01
#define RECEIVER_COMMAND_VOLUME_DOWN		0x02
#define RECEIVER_COMMAND_TOGGLE_MUTE		0x04
#define RECEIVER_COMMAND_TOGGLE_SUBWOOFER	0x08
#define RECEIVER_COMMAND_TOGGLE_SOURCE		0x10

void receiver_init(void (*cb)(uint8_t));
uint8_t receiver_get_command();

#endif /* RECEIVER_H_ */
