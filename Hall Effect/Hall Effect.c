/*
 * Hall_Effect.c
 *
 * Created: 10/11/2015 7:24:22 PM
 *  Author: karnazed
 */ 
#include "Hall Effect.h"
#include <avr/io.h>
#include <stdio.h>


void hall_effect_init(void)
{
	ADMUX |= (1<<REFS0);									// Select Vref=AVcc
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);	// Set prescaller to 128 and enable ADC
	DDRC &=~ (_BV(HE_SENSOR_1))|(_BV(HE_SENSOR_2));					// set sensors input
}

int read_sensor(int adc_pin) {
	ADMUX = (ADMUX & 0xF0) | (adc_pin & 0x0F);		// Select ADC channel with safety mask
	ADCSRA |= (1<<ADSC);							// Single conversion mode
	while (ADCSRA & _BV(ADSC));						// Wait for conversion to finish
	return ADC>>2;										// Return reading
}