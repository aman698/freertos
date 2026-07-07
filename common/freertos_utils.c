/**
 * @file freertos_utils.c
 * @brief Monitoring utilities — requires configUSE_TRACE_FACILITY = 1
 */
#include "freertos_utils.h"
#include "uart_debug.h"
#include "task.h"

void FreeRTOSUtils_PrintMemoryReport(void) {
  UartDebug_Printf("--- Memory Report ---\r\n");
  UartDebug_Printf("Heap free now : %u B\r\n", (unsigned)xPortGetFreeHeapSize());
  UartDebug_Printf("Heap min ever : %u B\r\n", (unsigned)xPortGetMinimumEverFreeHeapSize());
  UartDebug_Printf("This task HWM : %u words\r\n",
                   (unsigned)uxTaskGetStackHighWaterMark(NULL));
}

void FreeRTOSUtils_PrintTaskList(void) {
#if (configUSE_TRACE_FACILITY == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS == 1)
  char buf[512];
  vTaskList(buf);
  UartDebug_PrintRaw("--- Task List ---\r\n");
  UartDebug_PrintRaw(buf);
  UartDebug_PrintRaw("\r\n");
#else
  UartDebug_PrintRaw("Enable configUSE_STATS_FORMATTING_FUNCTIONS\r\n");
#endif
}
