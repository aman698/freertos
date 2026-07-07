/**
 * Advanced FreeRTOS Lab — paste into Core/Src/main.c USER CODE blocks
 */
#include "cmsis_os.h"
#include "app_events.h"

/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
    AppEvents_ButtonNotifyFromISR();
  }
}
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
/* USER CODE END 2 */

/*
 * If HAL_UART_RxCpltCallback is in app_command.c, do NOT duplicate here.
 * If linker error "multiple definition", keep callback in main.c only:
 *
 * void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
 *   extern void AppCommand_OnRxByteFromISR(uint8_t b);
 *   static uint8_t rx;
 *   ...
 * }
 */
