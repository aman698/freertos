/**
 ******************************************************************************
 * EXAMPLE 07 - main.c USER CODE snippets
 ******************************************************************************
 */

/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
static uint8_t g_uartRxByte;
extern UART_HandleTypeDef huart2;
extern void Uart_ISR_SendByteFromISR(uint8_t byte);
/* USER CODE END PV */

/* USER CODE BEGIN 2 */
HAL_UART_Receive_IT(&huart2, &g_uartRxByte, 1);
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2) {
    Uart_ISR_SendByteFromISR(g_uartRxByte);
    HAL_UART_Receive_IT(&huart2, &g_uartRxByte, 1);
  }
}
/* USER CODE END 4 */
