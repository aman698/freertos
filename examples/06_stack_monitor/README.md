# Example 06 — Stack Monitor & Heap Awareness

**Day:** 10  
**Hardware:** USART2 @ 115200

---

## Theory

### Stack high-water mark
```c
UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
```
Returns **minimum free stack words** ever remaining. Lower = closer to overflow.

| HWM value | Meaning |
|-----------|---------|
| 200+ | Safe |
| 50–100 | Watch closely |
| < 20 | Danger — increase stack |

### Heap
All `xQueueCreate`, `xTaskCreate`, `xSemaphoreCreate*` use `configTOTAL_HEAP_SIZE`.

Check free heap:
```c
size_t free = xPortGetFreeHeapSize();
```

### Stack overflow hook
In `FreeRTOSConfig.h`:
```c
#define configCHECK_FOR_STACK_OVERFLOW  2
```

Add to `freertos.c` or `stm32f4xx_it.c`:
```c
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  (void)xTask;
  (void)pcTaskName;
  for (;;);  /* halt — inspect pcTaskName in debugger */
}
```

---

## Practice

1. Add code from `freertos_additions.c` to your project (any example with 2+ tasks)
2. Enable `configUSE_TRACE_FACILITY` and stack overflow check in CubeMX
3. Monitor UART every 10 s

---

## Verify

| Check | Pass? |
|-------|-------|
| HWM printed for each task | |
| Free heap printed | |
| HWM > 50 words | |

### Danger experiment (then revert!)
Set `ledTask` stack to `64 * 4` → overflow hook or fault → restore `256 * 4`.

---

## Production checklist

- [ ] Every task has known stack HWM after stress test
- [ ] Heap lowest point recorded
- [ ] `configASSERT` on all Create calls
- [ ] No blocking calls in ISR
