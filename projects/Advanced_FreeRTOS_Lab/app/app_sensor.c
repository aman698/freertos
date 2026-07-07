#include "app_sensor.h"
#include "app_events.h"
#include "uart_debug.h"
#include "timers.h"

static QueueHandle_t s_sensorQueue;
static TimerHandle_t s_sampleTimer;
static uint32_t s_seq;

static void sample_timer_cb(TimerHandle_t t) {
  (void)t;
  AppSensorSample_t s;
  s.sequence = ++s_seq;
  s.value = 1000 + (s_seq % 100);
  s.tick = xTaskGetTickCount();
  xQueueSend(s_sensorQueue, &s, 0);
  xEventGroupSetBits(AppEvents_GetGroup(), APP_EVENT_BIT_SENSOR);
}

void AppSensor_Init(void) {
  s_sensorQueue = xQueueCreate(APP_SENSOR_QUEUE_LEN, sizeof(AppSensorSample_t));
  configASSERT(s_sensorQueue);
  s_sampleTimer = xTimerCreate("sns", pdMS_TO_TICKS(APP_SENSOR_PERIOD_MS), pdTRUE, NULL, sample_timer_cb);
  xTimerStart(s_sampleTimer, 0);
  UartDebug_Printf("[sensor] timer started %d ms\r\n", APP_SENSOR_PERIOD_MS);
}

QueueHandle_t AppSensor_GetQueue(void) {
  return s_sensorQueue;
}

void AppSensor_RequestSample(void) {
  AppSensorSample_t s;
  s.sequence = ++s_seq;
  s.value = 2000 + (s_seq % 50);
  s.tick = xTaskGetTickCount();
  xQueueSend(s_sensorQueue, &s, pdMS_TO_TICKS(10));
  xEventGroupSetBits(AppEvents_GetGroup(), APP_EVENT_BIT_SENSOR);
  UartDebug_PrintRaw("[sensor] manual sample queued\r\n");
}
