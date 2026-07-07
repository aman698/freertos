/**
 * @file freertos_utils.h
 * @brief Stack, heap, runtime stats helpers
 */
#ifndef FREERTOS_UTILS_H
#define FREERTOS_UTILS_H

#include "FreeRTOS.h"

void FreeRTOSUtils_PrintMemoryReport(void);
void FreeRTOSUtils_PrintTaskList(void);

#endif /* FREERTOS_UTILS_H */
