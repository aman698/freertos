/**
 ******************************************************************************
 * EXAMPLE 03 — syscalls_snippet.c
 * Merge into Core/Src/syscalls.c (add _write and includes)
 ******************************************************************************
 */

#include <sys/stat.h>
#include <errno.h>
#include "main.h"

extern UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len) {
  (void)file;
  if (HAL_UART_Transmit(&huart2, (uint8_t *)ptr, (uint16_t)len, HAL_MAX_DELAY) == HAL_OK) {
    return len;
  }
  errno = EIO;
  return -1;
}

/* Keep other syscalls from CubeMX (_read, _close, etc.) */
