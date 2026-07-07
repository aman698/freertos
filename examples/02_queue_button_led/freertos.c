/**
 ******************************************************************************
 * EXAMPLE 02 — freertos.c
 * Day 4: Queues + EXTI debounce pipeline
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
#define RAW_QUEUE_LEN     8
#define PRESS_QUEUE_LEN   4
#define DEBOUNCE_MS       40

osThreadId_t ledConsumerHandle;
osThreadId_t buttonDebounceHandle;

const osThreadAttr_t ledConsumer_attributes = {
  .name = "ledConsumer",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t buttonDebounce_attributes = {
  .name = "buttonDebounce",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

QueueHandle_t rawIsrQueue;
QueueHandle_t debouncedQueue;
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartLedConsumerTask(void *argument);
void StartButtonDebounceTask(void *argument);
void Button_ISR_SendEventFromISR(void);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  rawIsrQueue = xQueueCreate(RAW_QUEUE_LEN, sizeof(uint32_t));
  debouncedQueue = xQueueCreate(PRESS_QUEUE_LEN, sizeof(uint32_t));
  configASSERT(rawIsrQueue != NULL);
  configASSERT(debouncedQueue != NULL);

  buttonDebounceHandle = osThreadNew(StartButtonDebounceTask, NULL, &buttonDebounce_attributes);
  ledConsumerHandle = osThreadNew(StartLedConsumerTask, NULL, &ledConsumer_attributes);
  /* USER CODE END Init */
}

void Button_ISR_SendEventFromISR(void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  uint32_t evt = 1U;

  xQueueSendFromISR(rawIsrQueue, &evt, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void StartButtonDebounceTask(void *argument) {
  (void)argument;
  uint32_t evt;
  uint32_t pressId = 0;

  for (;;) {
    if (xQueueReceive(rawIsrQueue, &evt, portMAX_DELAY) == pdTRUE) {
      osDelay(DEBOUNCE_MS);

      if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
        pressId++;
        xQueueSend(debouncedQueue, &pressId, pdMS_TO_TICKS(10));
      }
    }
  }
}

void StartLedConsumerTask(void *argument) {
  (void)argument;
  uint32_t pressId;

  for (;;) {
    if (xQueueReceive(debouncedQueue, &pressId, portMAX_DELAY) == pdTRUE) {
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      (void)pressId;
    }
  }
}
