/**
 ******************************************************************************
 * EXAMPLE 02 — main_user_code.c
 * Paste into Core/Src/main.c
 ******************************************************************************
 */

/* ========== USER CODE BEGIN Includes ========== */
#include "cmsis_os.h"

/* Declared in freertos.c */
extern void Button_ISR_SendEventFromISR(void);
/* ========== USER CODE END Includes ========== */

/* ========== USER CODE BEGIN 0 ========== */
/**
 * HAL weak callback — called from EXTI ISR after NVIC routes interrupt.
 * Keep SHORT. Only queue send here.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
    Button_ISR_SendEventFromISR();
  }
}
/* ========== USER CODE END 0 ========== */

/* ========== USER CODE BEGIN 2 ========== */
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
/* ========== USER CODE END 2 ========== */
