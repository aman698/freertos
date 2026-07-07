#include "app_command.h"
#include "app_sensor.h"
#include "app_events.h"
#include "freertos_utils.h"
#include "uart_debug.h"
#include "stream_buffer.h"
#include <string.h>
#include <ctype.h>

static StreamBufferHandle_t s_stream;
static osThreadId_t s_cliTask;
static uint8_t s_rxByte;
extern UART_HandleTypeDef huart2;

static void cli_task(void *arg);
static void handle_line(char *line);

void AppCommand_Init(void) {
  const osThreadAttr_t attr = { .name = "cli", .stack_size = 1024*4, .priority = osPriorityNormal };
  s_stream = xStreamBufferCreate(APP_STREAM_SIZE, 1);
  configASSERT(s_stream);
  s_cliTask = osThreadNew(cli_task, NULL, &attr);
  AppEvents_SetCommReady();
}

void AppCommand_OnRxByteFromISR(uint8_t b) {
  BaseType_t w = pdFALSE;
  xStreamBufferSendFromISR(s_stream, &b, 1, &w);
  portYIELD_FROM_ISR(w);
}

void AppCommand_StartUartRx(void) {
  HAL_UART_Receive_IT(&huart2, &s_rxByte, 1);
}

static void cli_task(void *arg) {
  (void)arg;
  char line[64];
  size_t idx = 0;
  uint8_t b;

  UartDebug_PrintRaw("\r\n=== Advanced FreeRTOS Lab ===\r\n");
  UartDebug_PrintRaw("HELP | STATUS | SAMPLE | LED ON | LED OFF | TASKS\r\n");

  for (;;) {
    if (xStreamBufferReceive(s_stream, &b, 1, portMAX_DELAY) == 0) {
      continue;
    }
    if (b == '\r' || b == '\n') {
      if (idx > 0) {
        line[idx] = '\0';
        handle_line(line);
        idx = 0;
      }
      continue;
    }
    if (idx < sizeof(line) - 1) {
      line[idx++] = (char)b;
    }
  }
}

static void handle_line(char *line) {
  for (char *p = line; *p; p++) {
    *p = (char)toupper((unsigned char)*p);
  }
  if (strcmp(line, "HELP") == 0) {
    UartDebug_PrintRaw("HELP STATUS SAMPLE LED ON LED OFF TASKS\r\n");
  } else if (strcmp(line, "STATUS") == 0) {
    EventBits_t b = xEventGroupGetBits(AppEvents_GetGroup());
    UartDebug_Printf("Events: BTN=%d SNS=%d COMM=%d\r\n",
        !!(b & APP_EVENT_BIT_BTN), !!(b & APP_EVENT_BIT_SENSOR), !!(b & APP_EVENT_BIT_COMM));
    FreeRTOSUtils_PrintMemoryReport();
  } else if (strcmp(line, "SAMPLE") == 0) {
    AppSensor_RequestSample();
  } else if (strcmp(line, "LED ON") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  } else if (strcmp(line, "LED OFF") == 0) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
  } else if (strcmp(line, "TASKS") == 0) {
    FreeRTOSUtils_PrintTaskList();
  } else {
    UartDebug_Printf("Unknown: %s\r\n", line);
  }
}

/* Linker: provide ONE HAL_UART_RxCpltCallback — in main.c or here */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    AppCommand_OnRxByteFromISR(s_rxByte);
    HAL_UART_Receive_IT(&huart2, &s_rxByte, 1);
  }
}
