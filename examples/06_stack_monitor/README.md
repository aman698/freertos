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

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 4–7  
**Level:** L4 Advanced (hooks + memory)

### Breakpoints
| Where | Why |
|-------|-----|
| `vApplicationStackOverflowHook` | Catch overflow |
| Periodic HWM print in monitor task | Inspect values live |
| Any task with large local buffer | Stack pressure |

### Watch expressions
```
uxTaskGetStackHighWaterMark(NULL)
xPortGetFreeHeapSize()
xPortGetMinimumEverFreeHeapSize()
```

Call from monitor task breakpoint — `NULL` = current task HWM.

### Step drill — overflow (revert after!)
1. Set `ledTask` stack to `64 * 4` in attributes
2. Breakpoint in overflow hook → trigger fault path
3. **Variables:** `pcTaskName` — which task overflowed
4. **Expressions:** `uxTaskGetStackHighWaterMark(xTask)` near zero
5. Restore stack `256 * 4`

### Memory view
**Window → Memory** → address from stack pointer register when halted — see canary / garbage at stack end after overflow.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| HWM values match UART print | |
| Overflow hook catches intentional small stack | |
