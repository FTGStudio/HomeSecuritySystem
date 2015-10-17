/*
 * TestTask.h
 *
 * Created: 10/16/2015 10:16:35 PM
 *  Author: Michael
 */ 

#include "Source/include/FreeRTOS.h"
#include "Source/include/task.h"
#include "Source/include/queue.h"

extern xQueueHandle testMsgQ;

void vTestTask(void *pvParameters);