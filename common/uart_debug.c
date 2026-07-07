/**
 * @file uart_debug.c
 * @brief Mutex-protected printf — copy into Core/Src/ and add to build
 */
#include "uart_debug.h"
#include "main.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <stdio.h>
#include <stdarg.h>

extern UART_HandleTypeDef huart2;

static SemaphoreHandle_t s_uartMutex;

void UartDebug_Init(void) {
  s_uartMutex = xSemaphoreCreateMutex();
  configASSERT(s_uartMutex != NULL);
}

void UartDebug_Printf(const char *fmt, ...) {
  char buf[160];
  va_list args;
  int len;

  if (s_uartMutex == NULL) {
    return;
  }

  va_start(args, fmt);
  len = vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  if (len <= 0) {
    return;
  }

  if (xSemaphoreTake(s_uartMutex, pdMS_TO_TICKS(200)) == pdTRUE) {
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, (uint16_t)len, HAL_MAX_DELAY);
    xSemaphoreGive(s_uartMutex);
  }
}

void UartDebug_PrintRaw(const char *str) {
  size_t len = 0;
  if (str == NULL) {
    return;
  }
  while (str[len] != '\0') {
    len++;
  }
  if (xSemaphoreTake(s_uartMutex, pdMS_TO_TICKS(200)) == pdTRUE) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, (uint16_t)len, HAL_MAX_DELAY);
    xSemaphoreGive(s_uartMutex);
  }
}
