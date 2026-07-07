/**
 ******************************************************************************
 * EXAMPLE 07 - UART ISR -> Queue
 * Day 9 challenge: defer UART RX bytes from ISR to parser task
 ******************************************************************************
 *
 * CubeMX requirements:
 * - USART2 async 115200 8N1
 * - USART2 global interrupt enabled in NVIC
 * - FreeRTOS CMSIS_V2 enabled
 *
 * Copy this file into Core/Src/freertos.c USER CODE sections or merge manually.
 */

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Variables */
#define UART_RX_QUEUE_LEN  64U
#define UART_LINE_MAX      64U

extern UART_HandleTypeDef huart2;

QueueHandle_t uartRxQueue;
osThreadId_t uartParserHandle;

const osThreadAttr_t uartParser_attributes = {
  .name = "uartParser",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE END Variables */

/* USER CODE BEGIN FunctionPrototypes */
void StartUartParserTask(void *argument);
void Uart_ISR_SendByteFromISR(uint8_t byte);
static void Uart_ProcessLine(char *line);
static void Uart_WriteText(const char *text);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */
  uartRxQueue = xQueueCreate(UART_RX_QUEUE_LEN, sizeof(uint8_t));
  configASSERT(uartRxQueue != NULL);

  uartParserHandle = osThreadNew(StartUartParserTask, NULL, &uartParser_attributes);
  configASSERT(uartParserHandle != NULL);
  /* USER CODE END Init */
}

void Uart_ISR_SendByteFromISR(uint8_t byte)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  (void)xQueueSendFromISR(uartRxQueue, &byte, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void StartUartParserTask(void *argument)
{
  (void)argument;

  uint8_t byte;
  char line[UART_LINE_MAX];
  size_t index = 0U;

  Uart_WriteText("\r\nUART queue parser ready\r\n");
  Uart_WriteText("Commands: HELP | LED ON | LED OFF | PING\r\n");

  for (;;) {
    if (xQueueReceive(uartRxQueue, &byte, portMAX_DELAY) != pdTRUE) {
      continue;
    }

    if (byte == '\r' || byte == '\n') {
      if (index > 0U) {
        line[index] = '\0';
        Uart_ProcessLine(line);
        index = 0U;
      }
      continue;
    }

    if (index < (UART_LINE_MAX - 1U)) {
      line[index++] = (char)byte;
    } else {
      index = 0U;
      Uart_WriteText("ERR line too long\r\n");
    }
  }
}

static void Uart_ProcessLine(char *line)
{
  for (char *p = line; *p != '\0'; p++) {
    *p = (char)toupper((unsigned char)*p);
  }

  if (strcmp(line, "HELP") == 0) {
    Uart_WriteText("Commands: HELP LED ON LED OFF PING\r\n");
  } else if (strcmp(line, "LED ON") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    Uart_WriteText("OK LED ON\r\n");
  } else if (strcmp(line, "LED OFF") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    Uart_WriteText("OK LED OFF\r\n");
  } else if (strcmp(line, "PING") == 0) {
    Uart_WriteText("PONG\r\n");
  } else {
    Uart_WriteText("ERR unknown command\r\n");
  }
}

static void Uart_WriteText(const char *text)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)text, (uint16_t)strlen(text), HAL_MAX_DELAY);
}
