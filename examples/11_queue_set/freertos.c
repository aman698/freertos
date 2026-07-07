/**
 * EXAMPLE 11 — Queue Set Dispatcher (Day 14)
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "timers.h"
#include "uart_debug.h"

#define Q_LEN 4

QueueHandle_t btnQueue;
QueueHandle_t sensorQueue;
QueueHandle_t queueSet;
TimerHandle_t sensorTimer;

osThreadId_t dispatchHandle;
const osThreadAttr_t dispatchAttr = { .name = "dispatch", .stack_size = 512*4, .priority = osPriorityNormal };

void Button_ISR_SendFromISR(void);
void SensorTimerCb(TimerHandle_t t);
void StartDispatchTask(void *arg);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();

  btnQueue    = xQueueCreate(Q_LEN, sizeof(uint32_t));
  sensorQueue = xQueueCreate(Q_LEN, sizeof(uint32_t));
  configASSERT(btnQueue && sensorQueue);

  queueSet = xQueueCreateSet(Q_LEN * 2);
  configASSERT(queueSet);
  xQueueAddToSet(btnQueue, queueSet);
  xQueueAddToSet(sensorQueue, queueSet);

  sensorTimer = xTimerCreate("sns", pdMS_TO_TICKS(3000), pdTRUE, NULL, SensorTimerCb);
  xTimerStart(sensorTimer, 0);

  dispatchHandle = osThreadNew(StartDispatchTask, NULL, &dispatchAttr);
}

void Button_ISR_SendFromISR(void) {
  BaseType_t w = pdFALSE;
  uint32_t v = 1;
  xQueueSendFromISR(btnQueue, &v, &w);
  portYIELD_FROM_ISR(w);
}

void SensorTimerCb(TimerHandle_t t) {
  (void)t;
  uint32_t v = 42;
  xQueueSend(sensorQueue, &v, 0);
}

void StartDispatchTask(void *arg) {
  (void)arg;
  uint32_t data;
  QueueHandle_t active;

  UartDebug_Printf("[dispatch] waiting on queue set...\r\n");

  for (;;) {
    active = xQueueSelectFromSet(queueSet, portMAX_DELAY);
    if (active == btnQueue) {
      xQueueReceive(btnQueue, &data, 0);
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      UartDebug_Printf("[dispatch] BTN event\r\n");
    } else if (active == sensorQueue) {
      xQueueReceive(sensorQueue, &data, 0);
      UartDebug_Printf("[dispatch] SENSOR tick val=%lu\r\n", (unsigned long)data);
    }
  }
}
