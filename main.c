/*
 * freeRTOS.c
 *
 * Created: 10/12/2015 1:29:19 PM
 *  Author: Michael
*/ 
/*!
*
* \addtogroup main
* \defgroup  main
* @{
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
#include "LCD/LCD.h"
#include "WiFi/WiFi.h"
#include "TestTask.h"
#include "uart/uart.h"

#define F_CPU						8000000
#define mainLED_TASK_PRIORITY       ( tskIDLE_PRIORITY )
#define BAUD						9600 
#define MYUBRR						F_CPU/8/BAUD-1

void InitializeHardware(void);

int main(void)
{
	
	USART_Init(MYUBRR);
	stdout = &uart_output;
	stdin = &uart_input;
	
	hallEffectMsgQ = xQueueCreate(2, sizeof(HallEffectMsg_t));
	rtcMsgQ = xQueueCreate(2, sizeof(RTCMsg_t));
	lcdMsgQ = xQueueCreate(2, sizeof(LCDMsg_t));
	wifiMsgQ = xQueueCreate(2, sizeof(WiFiMsg_t));
	
	xTaskCreate( vRTCTask, ( signed char * ) "RTC", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vHallEffectTask, ( signed char * ) "HallEffect", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vLCDTask, ( signed char * ) "LCD", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vWifiTask, ( signed char * ) "WiFi", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vTestTask, ( signed char * ) "Test", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	
	vTaskStartScheduler();
}

/*!******************************************************************************
* \brief Initializes all of the hardware components 
*
*  Initializes the LCD, Hall-effect sensor, light sensor, keypad, 
*
* \param void
*
* \return none
********************************************************************************/
void InitializeHardware(void)
{
	
}

//! @}