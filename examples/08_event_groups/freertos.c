/**
 * EXAMPLE 08 — Event Groups
 * Day 11: Wait for multiple init conditions
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "uart_debug.h"

#define BIT_SENSOR_READY  (1UL << 0)
#define BIT_COMM_READY    (1UL << 1)
#define BIT_CAL_DONE      (1UL << 2)
#define ALL_READY_BITS    (BIT_SENSOR_READY | BIT_COMM_READY | BIT_CAL_DONE)

EventGroupHandle_t systemEventGroup;

osThreadId_t mainTaskHandle;
osThreadId_t sensorInitHandle;
osThreadId_t commInitHandle;
osThreadId_t calInitHandle;

const osThreadAttr_t mainAttr       = { .name = "main",   .stack_size = 512*4, .priority = osPriorityNormal };
const osThreadAttr_t sensorAttr     = { .name = "sensor", .stack_size = 256*4, .priority = osPriorityBelowNormal };
const osThreadAttr_t commAttr       = { .name = "comm",   .stack_size = 256*4, .priority = osPriorityBelowNormal };
const osThreadAttr_t calAttr        = { .name = "cal",    .stack_size = 256*4, .priority = osPriorityBelowNormal };

void StartMainTask(void *arg);
void StartSensorInit(void *arg);
void StartCommInit(void *arg);
void StartCalInit(void *arg);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();
  systemEventGroup = xEventGroupCreate();
  configASSERT(systemEventGroup != NULL);

  sensorInitHandle = osThreadNew(StartSensorInit, NULL, &sensorAttr);
  commInitHandle   = osThreadNew(StartCommInit, NULL, &commAttr);
  calInitHandle    = osThreadNew(StartCalInit, NULL, &calAttr);
  mainTaskHandle   = osThreadNew(StartMainTask, NULL, &mainAttr);
}

void StartSensorInit(void *arg) {
  (void)arg;
  osDelay(800);
  UartDebug_Printf("[sensor] ready\r\n");
  xEventGroupSetBits(systemEventGroup, BIT_SENSOR_READY);
  osThreadExit();
}

void StartCommInit(void *arg) {
  (void)arg;
  osDelay(1200);
  UartDebug_Printf("[comm] ready\r\n");
  xEventGroupSetBits(systemEventGroup, BIT_COMM_READY);
  osThreadExit();
}

void StartCalInit(void *arg) {
  (void)arg;
  osDelay(2000);
  UartDebug_Printf("[cal] done\r\n");
  xEventGroupSetBits(systemEventGroup, BIT_CAL_DONE);
  osThreadExit();
}

void StartMainTask(void *arg) {
  (void)arg;
  EventBits_t bits;

  UartDebug_Printf("[main] waiting for ALL bits...\r\n");

  bits = xEventGroupWaitBits(
      systemEventGroup,
      ALL_READY_BITS,
      pdTRUE,    /* clear on exit */
      pdTRUE,    /* wait for ALL — change to pdFALSE for ANY */
      portMAX_DELAY);

  if ((bits & ALL_READY_BITS) == ALL_READY_BITS) {
    UartDebug_Printf("[main] ALL READY — starting control loop\r\n");
    for (int i = 0; i < 5; i++) {
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      osDelay(100);
    }
  }

  for (;;) {
    osDelay(2000);
    UartDebug_Printf("[main] running\r\n");
  }
}
