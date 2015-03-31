/*
 * adc.c
 *
 * ADC handling. Used to read position of motor pot.
 *
 * Author: dreimalb
 */
#include "adc.h"

volatile uint16_t _adc_data[ADC_NUM_CHANNELS];
volatile uint32_t _adc_buffer[ADC_NUM_CHANNELS];
volatile uint8_t _adc_conversions = 0;

void adc_calc_values(uint8_t channel, uint16_t value) {
	uint32_t tmp = 0;
	if(_adc_conversions < ADC_SUM_CONVERSIONS)
	{
		_adc_buffer[channel] += value;
		_adc_conversions++;
	}
	else
	{
		tmp = _adc_buffer[channel]/ADC_SUM_CONVERSIONS;
		_adc_data[channel] = tmp;
		_adc_buffer[channel] = 0;
		_adc_conversions = 0;
	}
}

ISR(ADC_vect)
{
	static uint8_t channel = 0;
	static uint8_t update_channel = 0;
	uint8_t tmp;
	if(update_channel == 0)
	{
		adc_calc_values(channel, ADCW);
		channel = (channel+1)%ADC_NUM_CHANNELS;
		ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
		update_channel = 3;
	}
	else
	{
		tmp = ADCW;
		update_channel--;
	}
}

uint16_t adc_get_value(uint8_t c)
{
  return _adc_data[c];
}


void adc_init() 
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0) | (1<<ADATE) | (1<<ADIE); // Division = 32
	ADCSRB &= ~((1<<ADTS2) | (1<<ADTS1) | (1<<ADTS0));						// Free Running Mode
	ADCSRA |= (1<<ADSC);                     								// Erste Messung anschupsen
}

