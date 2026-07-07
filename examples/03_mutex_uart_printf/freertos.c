/**
 ******************************************************************************
 * EXAMPLE 03 — freertos.c
 * Requires: USART2 + syscalls_snippet.c in syscalls.c
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdio.h>
#include <stdarg.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
extern UART_HandleTypeDef huart2;

osThreadId_t fastPrintHandle;
osThreadId_t slowPrintHandle;

const osThreadAttr_t fastPrint_attributes = {
  .name = "fastPrint",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t slowPrint_attributes = {
  .name = "slowPrint",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

SemaphoreHandle_t uartMutex;
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void SafePrintf(const char *fmt, ...);
void StartFastPrintTask(void *argument);
void StartSlowPrintTask(void *argument);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  uartMutex = xSemaphoreCreateMutex();
  configASSERT(uartMutex != NULL);

  fastPrintHandle = osThreadNew(StartFastPrintTask, NULL, &fastPrint_attributes);
  slowPrintHandle = osThreadNew(StartSlowPrintTask, NULL, &slowPrint_attributes);
  /* USER CODE END Init */
}

void SafePrintf(const char *fmt, ...) {
  char buf[128];
  va_list args;
  int len;

  va_start(args, fmt);
  len = vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  if (len <= 0) {
    return;
  }

  if (xSemaphoreTake(uartMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, (uint16_t)len, HAL_MAX_DELAY);
    xSemaphoreGive(uartMutex);
  }
}

void StartFastPrintTask(void *argument) {
  (void)argument;
  uint32_t n = 0;

  for (;;) {
    SafePrintf("[FAST] msg %lu\r\n", n++);
    osDelay(150);
  }
}

void StartSlowPrintTask(void *argument) {
  (void)argument;
  uint32_t n = 0;

  for (;;) {
    SafePrintf("[SLOW] msg %lu\r\n", n++);
    osDelay(800);
  }
}
