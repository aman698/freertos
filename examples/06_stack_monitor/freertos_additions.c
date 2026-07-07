/**
 ******************************************************************************
 * EXAMPLE 06 — freertos_additions.c
 * Day 10: Add monitor task to ANY project with multiple tasks
 * Paste into Core/Src/freertos.c USER CODE sections
 * Requires: USART2 + printf retarget OR use SafePrintf from Example 03
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
osThreadId_t monitorTaskHandle;

const osThreadAttr_t monitorTask_attributes = {
  .name = "monitor",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartMonitorTask(void *argument);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
/* USER CODE END FunctionPrototypes */

/* Add inside MX_FREERTOS_Init(), after other tasks created: */
/*
  monitorTaskHandle = osThreadNew(StartMonitorTask, NULL, &monitorTask_attributes);
*/

void StartMonitorTask(void *argument) {
  (void)argument;

  for (;;) {
    printf("\r\n=== FreeRTOS Monitor ===\r\n");
    printf("Heap free: %u bytes\r\n", (unsigned)xPortGetFreeHeapSize());
    printf("Heap min ever: %u bytes\r\n", (unsigned)xPortGetMinimumEverFreeHeapSize());

    /* Current task (monitor) */
    printf("monitor      HWM: %u words\r\n",
           (unsigned)uxTaskGetStackHighWaterMark(NULL));

    /*
     * To print other tasks by name, use vTaskList() into a buffer:
     * char buf[512];
     * vTaskList(buf);
     * printf("%s\r\n", buf);
     * Requires configUSE_TRACE_FACILITY = 1
     */

    osDelay(10000);
  }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  (void)xTask;
  printf("STACK OVERFLOW in task: %s\r\n", pcTaskName);
  for (;;);
}
