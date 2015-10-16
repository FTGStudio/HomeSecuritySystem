/*
 * freeRTOS.c
 *
 * Created: 10/12/2015 1:29:19 PM
 *  Author: Michael
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "Source/include/FreeRTOS.h"
#include "Source/include/task.h"
#include "uart/uart.h"
#include "I2C/I2C.h"


#define F_CPU						8000000
#define mainLED_TASK_PRIORITY       ( tskIDLE_PRIORITY )
#define BAUD						9600 
#define MYUBRR						F_CPU/8/BAUD-1

void vLEDInit(void)
{
	// Set LED_O as output pin
	DDRB |= _BV(PB5);
}

void vLEDToggle(void)
{
	PORTB ^= _BV(PB5);
}

void vLEDFlashTask( void *pvParameters )
{
	printf("Initializing LED task");
	vLEDInit();
	portTickType xLastWakeTime;
	portTickType xFrequency = 1000;
	xLastWakeTime=xTaskGetTickCount();
	for( ;; )
	{
		vLEDToggle();
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
	
}

int main(void)
{
	USART_Init(MYUBRR);
	stdout = &uart_output;
	stdin = &uart_input;
	
	xTaskCreate( vLEDFlashTask, ( signed char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
	vTaskStartScheduler();
}