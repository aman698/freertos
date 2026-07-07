#include "app_monitor.h"
#include "freertos_utils.h"
#include "uart_debug.h"

static void monitor_task(void *arg) {
  (void)arg;
  for (;;) {
    osDelay(10000);
    UartDebug_PrintRaw("\r\n--- Monitor 10s ---\r\n");
    FreeRTOSUtils_PrintMemoryReport();
  }
}

void AppMonitor_Init(void) {
  const osThreadAttr_t attr = { .name = "monitor", .stack_size = 512*4, .priority = osPriorityLow };
  osThreadNew(monitor_task, NULL, &attr);
}
