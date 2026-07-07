/**
 * @file app_config.h
 * @brief Shared configuration for Advanced FreeRTOS Lab
 */
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "FreeRTOS.h"
#include "event_groups.h"

#define APP_EVENT_BIT_BTN     (1UL << 0)
#define APP_EVENT_BIT_SENSOR  (1UL << 1)
#define APP_EVENT_BIT_COMM    (1UL << 2)
#define APP_EVENT_ALL_READY   (APP_EVENT_BIT_BTN | APP_EVENT_BIT_SENSOR | APP_EVENT_BIT_COMM)

#define APP_SENSOR_QUEUE_LEN  8
#define APP_STREAM_SIZE     128
#define APP_SENSOR_PERIOD_MS 1000

typedef struct {
  uint32_t sequence;
  uint32_t value;
  TickType_t tick;
} AppSensorSample_t;

#endif /* APP_CONFIG_H */
