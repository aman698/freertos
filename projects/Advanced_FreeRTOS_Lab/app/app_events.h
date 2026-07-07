#ifndef APP_EVENTS_H
#define APP_EVENTS_H

#include "cmsis_os.h"
#include "app_config.h"

void AppEvents_Init(void);
EventGroupHandle_t AppEvents_GetGroup(void);
void AppEvents_ButtonNotifyFromISR(void);
void AppEvents_SetCommReady(void);

#endif
