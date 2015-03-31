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

void receiver_init ();
uint8_t receiver_is_source_valid(IRMP_DATA irmp_data);
uint8_t receiver_is_volume_up_command(IRMP_DATA irmp_data);
uint8_t receiver_is_volume_down_command(IRMP_DATA irmp_data);
uint8_t receiver_is_toggle_source_command(IRMP_DATA irmp_data);
uint8_t receiver_is_toggle_subwoofer_command(IRMP_DATA irmp_data);
uint8_t receiver_is_toggle_mute_command(IRMP_DATA irmp_data);

#endif /* RECEIVER_H_ */
