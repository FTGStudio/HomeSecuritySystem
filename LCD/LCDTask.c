/*
 * LCDTask.c
 *
 * Created: 10/16/2015 9:37:07 PM
 *  Author: Michael
 */ 

#include "LCD.h"

xQueueHandle lcdMsgQ;

void vLCDTask(void *pvParameters)
{
	uint32_t blockTime = portMAX_DELAY;
	LCDMsg_t msg;
	while(1)
	{
		
		if(xQueueReceive(lcdMsgQ, &msg, blockTime))
		{
			printf("\nLCD Message received\n");
		}
	}
}