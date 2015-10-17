/*
 * WiFi.h
 *
 * Created: 10/16/2015 9:45:50 PM
 *  Author: Michael
 */ 

#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

typedef struct{
	uint32_t dataPacket;
}WiFiMsg_t;

extern xQueueHandle wifiMsgQ;

void vWifiTask(void *pvParameters);