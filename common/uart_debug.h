/**
 * @file uart_debug.h
 * @brief Thread-safe UART helpers for all practice examples
 */
#ifndef UART_DEBUG_H
#define UART_DEBUG_H

#include "cmsis_os.h"
#include <stdint.h>

void UartDebug_Init(void);
void UartDebug_Printf(const char *fmt, ...);
void UartDebug_PrintRaw(const char *str);

#endif /* UART_DEBUG_H */
