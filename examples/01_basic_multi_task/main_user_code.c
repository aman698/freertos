/**
 ******************************************************************************
 * EXAMPLE 01 — main_user_code.c
 * Paste each block into matching USER CODE section in Core/Src/main.c
 * Do NOT replace the whole main.c — CubeMX generates clock/GPIO init.
 ******************************************************************************
 */

/* ========== USER CODE BEGIN Includes ========== */
#include "cmsis_os.h"
/* ========== USER CODE END Includes ========== */

/* ========== USER CODE BEGIN 2 ========== */
/* Optional: preload LED off */
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
/* ========== USER CODE END 2 ========== */

/* main() already has this flow from CubeMX — confirm it looks like: */
/*
int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();   // enable in CubeMX for Day 2+

  osKernelInitialize();
  MX_FREERTOS_Init();
  osKernelStart();

  while (1) { }  // never reached
}
*/

/* ========== USER CODE BEGIN 4 ========== */
/* Add helper functions here if needed */
/* ========== USER CODE END 4 ========== */
