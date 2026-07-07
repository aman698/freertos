/**
 ******************************************************************************
 * EXAMPLE 05 — freertos.c
 * Day 7: Counting semaphore — 5 workers, 3 slots
 * Requires: USART2 + syscalls retarget (Example 03)
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
#define MAX_SLOTS       3
#define NUM_WORKERS     5
#define WORKER_STACK    (512 * 4)

extern UART_HandleTypeDef huart2;

SemaphoreHandle_t slotSem;
osThreadId_t workerHandles[NUM_WORKERS];

const osThreadAttr_t workerAttr = {
  .name = "worker",
  .stack_size = WORKER_STACK,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartWorkerTask(void *argument);
static void UartPrint(const char *msg);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  slotSem = xSemaphoreCreateCounting(MAX_SLOTS, MAX_SLOTS);
  configASSERT(slotSem != NULL);

  for (uint32_t i = 0; i < NUM_WORKERS; i++) {
    workerHandles[i] = osThreadNew(StartWorkerTask, (void *)(uintptr_t)(i + 1U), &workerAttr);
  }
  /* USER CODE END Init */
}

static void UartPrint(const char *msg) {
  size_t len = 0;
  while (msg[len] != '\0') {
    len++;
  }
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, (uint16_t)len, HAL_MAX_DELAY);
}

void StartWorkerTask(void *argument) {
  uint32_t id = (uint32_t)(uintptr_t)argument;
  char line[64];

  for (;;) {
    snprintf(line, sizeof(line), "[W%lu] waiting for slot...\r\n", (unsigned long)id);
    UartPrint(line);

    if (xSemaphoreTake(slotSem, portMAX_DELAY) == pdTRUE) {
      snprintf(line, sizeof(line), "[W%lu] >>> IN critical section\r\n", (unsigned long)id);
      UartPrint(line);

      osDelay(1500);  /* simulate shared resource use */

      snprintf(line, sizeof(line), "[W%lu] <<< OUT releasing slot\r\n", (unsigned long)id);
      UartPrint(line);

      xSemaphoreGive(slotSem);
    }

    osDelay(500);
  }
}
