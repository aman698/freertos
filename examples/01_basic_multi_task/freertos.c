/**
 ******************************************************************************
 * EXAMPLE 01 — freertos.c
 * Copy into: Core/Src/freertos.c (USER CODE sections)
 * Days 1-3: Tasks, priorities, vTaskDelay, vTaskDelayUntil
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
osThreadId_t ledTaskHandle;
osThreadId_t heartbeatTaskHandle;

const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t heartbeatTask_attributes = {
  .name = "heartbeatTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartLedTask(void *argument);
void StartHeartbeatTask(void *argument);
void MX_FREERTOS_Init(void);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  ledTaskHandle = osThreadNew(StartLedTask, NULL, &ledTask_attributes);
  heartbeatTaskHandle = osThreadNew(StartHeartbeatTask, NULL, &heartbeatTask_attributes);
  /* USER CODE END Init */
}

/**
 * LED task — Day 1: osDelay(200)
 * Day 3: switch to vTaskDelayUntil for exact 300 ms period (see README)
 */
void StartLedTask(void *argument) {
  (void)argument;

#if 0 /* Day 3: enable this block, disable osDelay loop below */
  TickType_t lastWake = xTaskGetTickCount();
  for (;;) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(300));
  }
#else
  for (;;) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    osDelay(200);
  }
#endif
}

/**
 * Lower priority task — proves scheduler runs it when LED task blocks.
 * Day 2: uncomment printf after adding syscalls retarget.
 */
void StartHeartbeatTask(void *argument) {
  (void)argument;
  uint32_t count = 0;

  for (;;) {
    count++;
    /* printf("[heartbeat] count=%lu tick=%lu\r\n",
            count, (unsigned long)xTaskGetTickCount()); */
    (void)count;
    osDelay(1000);
  }
}

/* USER CODE BEGIN Application */
/* Day 2 experiment: add urgentTask here — see README.md */
/* USER CODE END Application */
