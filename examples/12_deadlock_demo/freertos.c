/**
 * EXAMPLE 12 — Priority Inversion & Deadlock (Day 15)
 * Set USE_DEADLOCK_DEMO to 1 to see intentional deadlock
 */
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "uart_debug.h"

#define USE_DEADLOCK_DEMO  0   /* 0 = inversion demo, 1 = deadlock demo */

SemaphoreHandle_t mutexL;
#if USE_DEADLOCK_DEMO
SemaphoreHandle_t mutexM1;
SemaphoreHandle_t mutexM2;
#endif

osThreadId_t lowHandle, medHandle, highHandle;
#if USE_DEADLOCK_DEMO
osThreadId_t taskAHandle, taskBHandle;
#endif

const osThreadAttr_t lowAttr  = { .name = "low",  .stack_size = 512*4, .priority = osPriorityLow };
const osThreadAttr_t medAttr  = { .name = "med",  .stack_size = 512*4, .priority = osPriorityNormal };
const osThreadAttr_t highAttr = { .name = "high", .stack_size = 512*4, .priority = osPriorityHigh };

void StartLow(void *a);
void StartMed(void *a);
void StartHigh(void *a);
#if USE_DEADLOCK_DEMO
void StartTaskA(void *a);
void StartTaskB(void *a);
#endif

void MX_FREERTOS_Init(void) {
  UartDebug_Init();

#if USE_DEADLOCK_DEMO
  mutexM1 = xSemaphoreCreateMutex();
  mutexM2 = xSemaphoreCreateMutex();
  taskAHandle = osThreadNew(StartTaskA, NULL, &lowAttr);
  taskBHandle = osThreadNew(StartTaskB, NULL, &medAttr);
#else
  mutexL = xSemaphoreCreateMutex();
  lowHandle  = osThreadNew(StartLow, NULL, &lowAttr);
  medHandle  = osThreadNew(StartMed, NULL, &medAttr);
  highHandle = osThreadNew(StartHigh, NULL, &highAttr);
#endif
}

#if !USE_DEADLOCK_DEMO
void StartLow(void *a) {
  (void)a;
  xSemaphoreTake(mutexL, portMAX_DELAY);
  UartDebug_PrintRaw("[low] got mutex, working 2s...\r\n");
  osDelay(2000);
  xSemaphoreGive(mutexL);
  UartDebug_PrintRaw("[low] released\r\n");
  for (;;) { osDelay(1000); }
}

void StartMed(void *a) {
  (void)a;
  osDelay(100);
  UartDebug_PrintRaw("[med] busy loop 3s (no mutex)\r\n");
  for (int i = 0; i < 30; i++) {
    osDelay(100);
  }
  UartDebug_PrintRaw("[med] done\r\n");
  for (;;) { osDelay(1000); }
}

void StartHigh(void *a) {
  (void)a;
  osDelay(200);
  UartDebug_PrintRaw("[high] waiting for mutex...\r\n");
  xSemaphoreTake(mutexL, portMAX_DELAY);
  UartDebug_PrintRaw("[high] GOT mutex — inversion test PASS\r\n");
  xSemaphoreGive(mutexL);
  for (;;) { osDelay(1000); }
}
#else
/* WRONG ORDER — causes deadlock. Fix: both tasks take M1 then M2 */
void StartTaskA(void *a) {
  (void)a;
  xSemaphoreTake(mutexM1, portMAX_DELAY);
  UartDebug_PrintRaw("[A] has M1, delay 500ms\r\n");
  osDelay(500);
  UartDebug_PrintRaw("[A] wants M2...\r\n");
  xSemaphoreTake(mutexM2, portMAX_DELAY);
  UartDebug_PrintRaw("[A] got both\r\n");
  xSemaphoreGive(mutexM2);
  xSemaphoreGive(mutexM1);
  for (;;) { osDelay(1000); }
}

void StartTaskB(void *a) {
  (void)a;
  osDelay(50);
  xSemaphoreTake(mutexM2, portMAX_DELAY);
  UartDebug_PrintRaw("[B] has M2, delay 500ms\r\n");
  osDelay(500);
  UartDebug_PrintRaw("[B] wants M1... DEADLOCK\r\n");
  xSemaphoreTake(mutexM1, portMAX_DELAY);
  for (;;) { osDelay(1000); }
}
#endif
