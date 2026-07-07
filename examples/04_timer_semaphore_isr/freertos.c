/**
 ******************************************************************************
 * EXAMPLE 04 — freertos.c
 * Days 5, 8, 9: Binary semaphore, software timer, ISR deferral
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
#define BLINK_TIMER_PERIOD_MS  500
#define DEBOUNCE_MS            40

osThreadId_t workerTaskHandle;

const osThreadAttr_t workerTask_attributes = {
  .name = "workerTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

TimerHandle_t blinkTimer;
SemaphoreHandle_t buttonSem;

extern UART_HandleTypeDef huart2;  /* optional, if USART2 enabled */
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void BlinkTimerCallback(TimerHandle_t xTimer);
void Button_ISR_GiveSemFromISR(void);
void StartWorkerTask(void *argument);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  buttonSem = xSemaphoreCreateBinary();
  configASSERT(buttonSem != NULL);

#if 1  /* Day 8: keep enabled. Day 5 only: set to 0 to disable timer */
  blinkTimer = xTimerCreate(
      "blinkTmr",
      pdMS_TO_TICKS(BLINK_TIMER_PERIOD_MS),
      pdTRUE,
      NULL,
      BlinkTimerCallback);
  configASSERT(blinkTimer != NULL);
  xTimerStart(blinkTimer, 0);
#endif

  workerTaskHandle = osThreadNew(StartWorkerTask, NULL, &workerTask_attributes);
  /* USER CODE END Init */
}

void BlinkTimerCallback(TimerHandle_t xTimer) {
  (void)xTimer;
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void Button_ISR_GiveSemFromISR(void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xSemaphoreGiveFromISR(buttonSem, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void StartWorkerTask(void *argument) {
  (void)argument;
  uint32_t pressCount = 0;

  for (;;) {
    if (xSemaphoreTake(buttonSem, portMAX_DELAY) == pdTRUE) {
      osDelay(DEBOUNCE_MS);

      if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
        pressCount++;

#if 0  /* Enable when USART2 + syscalls retarget added (Example 03) */
        printf("Button #%lu  stackHWM=%u\r\n",
               pressCount,
               (unsigned)uxTaskGetStackHighWaterMark(NULL));
#else
        /* Day 5 without UART: toggle LED on press (disable timer first) */
        /* HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); */
        (void)pressCount;
#endif
      }
    }
  }
}
