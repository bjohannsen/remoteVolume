#ifndef MOTORPOT_H_
#define MOTORPOT_H_
#include <math.h>
#include <avr/io.h>
#include <stdio.h>

#define MOTOR_PORT				PORTD
#define MOTOR_DDR				DDRD
#define MOTOR_B					(1<<PORTD0)
#define MOTOR_A					(1<<PORTD1)

#define MOTOR_ADC_TOLERANCE 	0.1

#define MOTOR_STOP				(MOTOR_PORT &= ~(MOTOR_A | MOTOR_B))
#define MOTOR_RUN_CW			(MOTOR_PORT |= MOTOR_A)
#define MOTOR_RUN_CCW			(MOTOR_PORT |= MOTOR_B)

void motor_check_position(uint16_t adc_value);
void motor_init();
void motor_update_target(uint8_t gain_level);


#endif /* MOTORPOT_H_ */
