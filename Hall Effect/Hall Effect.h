/*
 * Hall_Effect.h
 *
 * Created: 10/11/2015 7:24:53 PM
 *  Author: karnazed
 */ 


#ifndef HALL EFFECT_H_
#define HALL EFFECT_H_

#define HALL_EFFECT_PORT PORTC
#define HE_SENSOR_1 1
#define HE_SENSOR_2 2
 

int read_sensor(int adc_pin);
void hall_effect_init(void);


#endif /* HALL EFFECT_H_ */