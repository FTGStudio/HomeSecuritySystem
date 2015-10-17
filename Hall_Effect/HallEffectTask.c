/*
 * hallEffectTask.c
 *
 * Created: 10/16/2015 9:04:04 PM
 *  Author: Michael
 */ 

#include "Hall_Effect.h"
#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

xQueueHandle hallEffectMsgQ;

void vHallEffectTask(void *pvParameters)
{
	uint32_t blockTime = portMAX_DELAY;
	HallEffectMsg_t msg;
	while(1)
	{
		if(xQueueReceive(hallEffectMsgQ, &msg, blockTime))
		{
			printf("Hall effect voltage %d", (int)msg.hallEffectData);
		}
	}
}