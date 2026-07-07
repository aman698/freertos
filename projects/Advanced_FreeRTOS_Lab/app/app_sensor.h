#ifndef APP_SENSOR_H
#define APP_SENSOR_H

#include "app_config.h"
#include "queue.h"

void AppSensor_Init(void);
QueueHandle_t AppSensor_GetQueue(void);
void AppSensor_RequestSample(void);

#endif
