/**
 * Advanced FreeRTOS Lab — Core/Src/freertos.c (USER CODE merge)
 * Day 20 Capstone
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "uart_debug.h"

#include "app_config.h"
#include "app_events.h"
#include "app_sensor.h"
#include "app_command.h"
#include "app_monitor.h"

osThreadId_t processTaskHandle;
const osThreadAttr_t processAttr = {
  .name = "process", .stack_size = 768*4, .priority = osPriorityNormal
};

void StartProcessTask(void *arg);
void vApplicationStackOverflowHook(TaskHandle_t t, char *name);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();

  AppEvents_Init();
  AppSensor_Init();
  AppCommand_Init();
  AppMonitor_Init();

  processTaskHandle = osThreadNew(StartProcessTask, NULL, &processAttr);

  AppCommand_StartUartRx();
  UartDebug_PrintRaw("[init] subsystems started, waiting for process ready\r\n");
}

void StartProcessTask(void *arg) {
  (void)arg;
  EventBits_t bits;
  AppSensorSample_t sample;

  bits = xEventGroupWaitBits(
      AppEvents_GetGroup(),
      APP_EVENT_BIT_COMM,
      pdFALSE,
      pdTRUE,
      portMAX_DELAY);

  if (bits & APP_EVENT_BIT_COMM) {
    UartDebug_PrintRaw("[process] COMM ready — SYSTEM ONLINE\r\n");
  }

  for (;;) {
    if (xQueueReceive(AppSensor_GetQueue(), &sample, pdMS_TO_TICKS(500)) == pdTRUE) {
      UartDebug_Printf("[process] seq=%lu val=%lu tick=%lu\r\n",
          (unsigned long)sample.sequence,
          (unsigned long)sample.value,
          (unsigned long)sample.tick);
    }
  }
}

void vApplicationStackOverflowHook(TaskHandle_t t, char *name) {
  (void)t;
  UartDebug_Printf("STACK OVERFLOW: %s\r\n", name);
  for (;;);
}
