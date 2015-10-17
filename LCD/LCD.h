/*
 * LCD.h
 *
 * Created: 10/16/2015 9:37:44 PM
 *  Author: Michael
 */ 

#include "../Source/include/FreeRTOS.h"
#include "../Source/include/task.h"
#include "../Source/include/queue.h"

typedef struct{
	char *displayString;
}LCDMsg_t;

extern xQueueHandle lcdMsgQ;

void vLCDTask(void *pvParameters);