/**
 * EXAMPLE 10 — Stream Buffer UART CLI (Day 13)
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "uart_debug.h"
#include "freertos_utils.h"
#include <string.h>
#include <ctype.h>

#define STREAM_SIZE     128
#define RX_BYTE_BUF     1
#define CMD_MAX         64

StreamBufferHandle_t uartStream;
osThreadId_t cliTaskHandle;
const osThreadAttr_t cliAttr = { .name = "cli", .stack_size = 1024*4, .priority = osPriorityNormal };

static uint8_t s_rxByte;
extern UART_HandleTypeDef huart2;

void Uart_RX_PushByteFromISR(uint8_t b);
void StartCliTask(void *arg);
static void process_line(char *line);

void MX_FREERTOS_Init(void) {
  UartDebug_Init();
  uartStream = xStreamBufferCreate(STREAM_SIZE, 1);
  configASSERT(uartStream != NULL);
  cliTaskHandle = osThreadNew(StartCliTask, NULL, &cliAttr);
}

void Uart_RX_PushByteFromISR(uint8_t b) {
  BaseType_t woken = pdFALSE;
  xStreamBufferSendFromISR(uartStream, &b, 1, &woken);
  portYIELD_FROM_ISR(woken);
}

void StartCliTask(void *arg) {
  (void)arg;
  char line[CMD_MAX];
  size_t idx = 0;
  uint8_t b;

  UartDebug_Printf("\r\n=== Stream Buffer CLI ===\r\nHELP | LED ON | LED OFF | STATUS\r\n");

  for (;;) {
    size_t n = xStreamBufferReceive(uartStream, &b, 1, portMAX_DELAY);
    if (n == 0) {
      continue;
    }

    if (b == '\r' || b == '\n') {
      if (idx > 0) {
        line[idx] = '\0';
        process_line(line);
        idx = 0;
      }
      continue;
    }

    if (idx < (CMD_MAX - 1)) {
      line[idx++] = (char)b;
    }
  }
}

static void process_line(char *line) {
  for (char *p = line; *p; p++) {
    *p = (char)toupper((unsigned char)*p);
  }

  if (strcmp(line, "HELP") == 0) {
    UartDebug_PrintRaw("Commands: HELP LED ON LED OFF STATUS\r\n");
  } else if (strcmp(line, "LED ON") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    UartDebug_PrintRaw("OK LED ON\r\n");
  } else if (strcmp(line, "LED OFF") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    UartDebug_PrintRaw("OK LED OFF\r\n");
  } else if (strcmp(line, "STATUS") == 0) {
    FreeRTOSUtils_PrintMemoryReport();
  } else {
    UartDebug_Printf("Unknown: %s\r\n", line);
  }
}

/* Call from main after MX_USART2_UART_Init: */
void Uart_CLI_StartRx(void) {
  HAL_UART_Receive_IT(&huart2, &s_rxByte, RX_BYTE_BUF);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    Uart_RX_PushByteFromISR(s_rxByte);
    HAL_UART_Receive_IT(&huart2, &s_rxByte, RX_BYTE_BUF);
  }
}
