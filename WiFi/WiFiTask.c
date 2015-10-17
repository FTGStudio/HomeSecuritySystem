/*
 * WiFiTask.c
 *
 * Created: 10/16/2015 9:44:55 PM
 *  Author: Michael
 */ 

#include "WiFi.h"

xQueueHandle wifiMsgQ;

void vWifiTask(void *pvParameters)
{
	uint32_t blockTime = portMAX_DELAY;
	WiFiMsg_t msg;
	while(1)
	{
		if(xQueueReceive(wifiMsgQ, &msg, blockTime))
		{
			
		}
	}
}