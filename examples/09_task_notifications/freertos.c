/**
 * EXAMPLE 09 — Task Notifications (Day 12)
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart_debug.h"

osThreadId_t workerTaskHandle;
const osThreadAttr_t workerAttr = {
  .name = "worker", .stack_size = 512*4, .priority = osPriorityNormal
};

void Button_ISR_NotifyFromISR(void);
void StartWorkerTask(void *arg);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();
  workerTaskHandle = osThreadNew(StartWorkerTask, NULL, &workerAttr);
}

void Button_ISR_NotifyFromISR(void) {
  BaseType_t woken = pdFALSE;
  vTaskNotifyGiveFromISR(workerTaskHandle, &woken);
  portYIELD_FROM_ISR(woken);
}

void StartWorkerTask(void *arg) {
  (void)arg;
  uint32_t count = 0;

  UartDebug_Printf("[worker] waiting for notifications...\r\n");

  for (;;) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    osDelay(40);

    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
      count++;
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      UartDebug_Printf("[worker] notify #%lu\r\n", (unsigned long)count);
    }
  }
}
