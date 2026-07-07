#include "app_events.h"
#include "uart_debug.h"

static EventGroupHandle_t s_events;
static osThreadId_t s_btnWorker;

static void AppEvents_BtnWorker(void *arg) {
  (void)arg;
  for (;;) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    osDelay(40);
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
      xEventGroupSetBits(s_events, APP_EVENT_BIT_BTN);
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      UartDebug_PrintRaw("[event] BTN bit set\r\n");
    }
  }
}

void AppEvents_Init(void) {
  const osThreadAttr_t attr = { .name = "btnEvt", .stack_size = 384*4, .priority = osPriorityAboveNormal };
  s_events = xEventGroupCreate();
  configASSERT(s_events);
  s_btnWorker = osThreadNew(AppEvents_BtnWorker, NULL, &attr);
}

EventGroupHandle_t AppEvents_GetGroup(void) {
  return s_events;
}

void AppEvents_ButtonNotifyFromISR(void) {
  BaseType_t w = pdFALSE;
  vTaskNotifyGiveFromISR(s_btnWorker, &w);
  portYIELD_FROM_ISR(w);
}

void AppEvents_SetCommReady(void) {
  xEventGroupSetBits(s_events, APP_EVENT_BIT_COMM);
}
