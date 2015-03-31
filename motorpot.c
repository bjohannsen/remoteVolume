/*
 * motorpot.c
 *
 * Controlling of motorpot.
 *
 * Author: dreimalb
 */
#include "motorpot.h"

uint16_t _motor_target = 0;

uint8_t motor_calc_adc_tolerance(uint16_t adc_value)
{
	double tolerance = (double)adc_value*MOTOR_ADC_TOLERANCE;
	return (uint8_t) tolerance+1;
}

void motor_check_position(uint16_t adc_value)
{
	uint8_t adc_tolerance = motor_calc_adc_tolerance(adc_value);

	MOTOR_STOP;
	if(adc_value > _motor_target+adc_tolerance)
	{
		MOTOR_RUN_CW;
	}
	else if(adc_value < _motor_target-adc_tolerance)
	{
		MOTOR_RUN_CCW;
	}
}

void motor_init() {
    MOTOR_DDR |= (MOTOR_A|MOTOR_B);
}

void motor_update_target(uint8_t gain_level)
{
	double base = 0.62518 * (double)gain_level;
	_motor_target = pow(base, 2.55);
}

