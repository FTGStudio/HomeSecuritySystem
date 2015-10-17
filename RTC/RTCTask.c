/*
 * RTCTask.c
 *
 * Created: 10/16/2015 9:10:31 PM
 *  Author: Michael
 */ 

#include "RTC.h"
#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

xQueueHandle rtcMsgQ;

void vRTCTask( void *pvParameters )
{
	uint32_t blockTime = portMAX_DELAY;
	RTCMsg_t msg;
	while(1)
	{
		
		if(xQueueReceive(rtcMsgQ, &msg, blockTime))
		{
			printf("\nRTC Message received\n");
		}
	}
}
