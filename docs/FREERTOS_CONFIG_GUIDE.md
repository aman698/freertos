# FreeRTOS Config — Advanced Labs (CubeMX reference)

Add or verify these in **FreeRTOS → Config parameters** or `FreeRTOSConfig.h`:

```c
#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE                 0   /* Day 19: set 1 */
#define configCPU_CLOCK_HZ                      SystemCoreClock
#define configTICK_RATE_HZ                      1000
#define configMAX_PRIORITIES                    56
#define configMINIMAL_STACK_SIZE                128
#define configTOTAL_HEAP_SIZE                   24576
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_TRACE_FACILITY                1
#define configUSE_16_BIT_TICKS                  0
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_EVENT_GROUPS                  1
#define configUSE_STREAM_BUFFERS                1
#define configUSE_QUEUE_SETS                    1
#define configQUEUE_REGISTRY_SIZE               8
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (osPriorityHigh)
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            256
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configUSE_MALLOC_FAILED_HOOK            1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

/* Day 16 optional — runtime stats */
#define configGENERATE_RUN_TIME_STATS           0
```

## NVIC (STM32F411)

Cortex-M4 priority: **lower number = higher urgency**.

ISRs calling FreeRTOS `FromISR` APIs must be at **logically lower or equal priority** than `configMAX_SYSCALL_INTERRUPT_PRIORITY`.

In CubeMX NVIC: set USART/EXTI preemption priority to **5 or higher number** (weaker urgency) if you get `configASSERT` in ISR.

## Hooks — add to freertos.c

```c
void vApplicationMallocFailedHook(void) {
  for (;;);  /* heap exhausted */
}
```
