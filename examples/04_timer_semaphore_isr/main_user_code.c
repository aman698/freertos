/**
 ******************************************************************************
 * EXAMPLE 04 — main_user_code.c
 ******************************************************************************
 */

/* ========== USER CODE BEGIN Includes ========== */
#include "cmsis_os.h"
extern void Button_ISR_GiveSemFromISR(void);
/* ========== USER CODE END Includes ========== */

/* ========== USER CODE BEGIN 0 ========== */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
    Button_ISR_GiveSemFromISR();
  }
}
/* ========== USER CODE END 0 ========== */
