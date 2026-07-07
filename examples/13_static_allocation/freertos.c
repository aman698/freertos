/**
 * EXAMPLE 13 — Static Queue Allocation (Day 18)
 * Same logic as Example 02 — no heap for queues
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "uart_debug.h"

#define RAW_LEN    4
#define PRESS_LEN  4

static StaticQueue_t rawStruct, pressStruct;
static uint8_t rawStorage[RAW_LEN * sizeof(uint32_t)];
static uint8_t pressStorage[PRESS_LEN * sizeof(uint32_t)];

QueueHandle_t rawQueue;
QueueHandle_t pressQueue;

osThreadId_t debounceHandle, ledHandle;
const osThreadAttr_t debAttr = { .name = "deb", .stack_size = 256*4, .priority = osPriorityAboveNormal };
const osThreadAttr_t ledAttr = { .name = "led", .stack_size = 256*4, .priority = osPriorityNormal };

void Button_ISR_SendFromISR(void);
void StartDebounce(void *a);
void StartLed(void *a);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();

  rawQueue = xQueueCreateStatic(RAW_LEN, sizeof(uint32_t), rawStorage, &rawStruct);
  pressQueue = xQueueCreateStatic(PRESS_LEN, sizeof(uint32_t), pressStorage, &pressStruct);
  configASSERT(rawQueue && pressQueue);

  UartDebug_Printf("Heap after static queues: %u B\r\n", (unsigned)xPortGetFreeHeapSize());

  debounceHandle = osThreadNew(StartDebounce, NULL, &debAttr);
  ledHandle = osThreadNew(StartLed, NULL, &ledAttr);
}

void Button_ISR_SendFromISR(void) {
  BaseType_t w = pdFALSE;
  uint32_t v = 1;
  xQueueSendFromISR(rawQueue, &v, &w);
  portYIELD_FROM_ISR(w);
}

void StartDebounce(void *a) {
  (void)a;
  uint32_t v, id = 0;
  for (;;) {
    xQueueReceive(rawQueue, &v, portMAX_DELAY);
    osDelay(40);
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
      id++;
      xQueueSend(pressQueue, &id, 0);
    }
  }
}

void StartLed(void *a) {
  (void)a;
  uint32_t id;
  for (;;) {
    xQueueReceive(pressQueue, &id, portMAX_DELAY);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    UartDebug_Printf("Static press #%lu\r\n", (unsigned long)id);
  }
}
