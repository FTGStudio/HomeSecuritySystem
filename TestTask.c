/*
 * TestTask.c
 *
 * Created: 10/16/2015 10:15:36 PM
 *  Author: Michael
 */ 

#include "TestTask.h"
#include "Hall_Effect/Hall_Effect.h"
#include "LCD/LCD.h"
#include "RTC/RTC.h"
#include "WiFi/WiFi.h"

void vTestTask(void *pvParameters)
{
	HallEffectMsg_t hallEffectMessage;
	LCDMsg_t LCDMessage;
	RTCMsg_t RTCMessage;
	WiFiMsg_t WifiMessage;
	
	while(1)
	{
		xQueueSend(hallEffectMsgQ, &hallEffectMessage, 10);
		vTaskDelay(1000);
		xQueueSend(lcdMsgQ, &LCDMessage, 10);
		vTaskDelay(1000);
		xQueueSend(rtcMsgQ, &RTCMessage, 10);
		vTaskDelay(1000);
		xQueueSend(wifiMsgQ, &WifiMessage, 10);
		vTaskDelay(1000);	
	}
}