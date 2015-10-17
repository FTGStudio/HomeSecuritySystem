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
#include "Source/include/queue.h"
#include "I2C/I2C.h"
#include "RTC/RTC.h"
#include "Hall_Effect/Hall_Effect.h"
#include "uart/uart.h"

#define F_CPU						8000000
#define mainLED_TASK_PRIORITY       ( tskIDLE_PRIORITY )
#define BAUD						9600 
#define MYUBRR						F_CPU/8/BAUD-1



int main(void)
{
	
	USART_Init(MYUBRR);
	stdout = &uart_output;
	stdin = &uart_input;
	
	hallEffectMsgQ = xQueueCreate(2, sizeof(HallEffectMsg_t));
	rtcMsgQ = xQueueCreate(2, sizeof(RTCMsg_t));
	
	xTaskCreate( vRTCTask, ( signed char * ) "RTC", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vHallEffectTask, ( signed char * ) "HallEffect", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	vTaskStartScheduler();
}