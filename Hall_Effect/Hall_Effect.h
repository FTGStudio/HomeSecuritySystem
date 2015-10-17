/*
 * Hall_Effect.h
 *
 * Created: 10/11/2015 7:24:53 PM
 *  Author: karnazed
 */ 


#ifndef HALL_EFFECT_H_
#define HALL_EFFECT_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

#define HALL_EFFECT_PORT PORTC
#define HE_SENSOR_1 1
#define HE_SENSOR_2 2

typedef struct  
{
	uint32_t hallEffectData;
}HallEffectMsg_t;

extern xQueueHandle hallEffectMsgQ; 

int read_sensor(int adc_pin);
void hall_effect_init(void);
void vHallEffectTask(void *pvParameters);

#endif /* HALL EFFECT_H_ */