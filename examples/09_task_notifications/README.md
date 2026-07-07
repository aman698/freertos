# Example 09 — Task Notifications

**Day 12** | Replaces binary semaphore with direct task notify.

---

## Theory (deep)

### Internal mechanism
Each task has `ulNotifiedValue` (32-bit). `xTaskNotifyGive` increments; `ulTaskNotifyTake` decrements/blocks.

### Compared to semaphore
| | Task Notify | Binary Semaphore |
|---|-------------|------------------|
| RAM | 0 extra objects | ~80 bytes |
| Speed | Faster | Good |
| Multiple waiters | No | Yes (one taker) |
| Count > 1 | Yes (notification count) | Binary only |

### Indexed notifications (FreeRTOS v8.2+)
`configTASK_NOTIFICATION_ARRAY_ENTRIES` — multiple virtual "channels" per task.

### ISR API
```c
vTaskNotifyGiveFromISR(taskHandle, &woken);
```

---

## Practice
Copy `freertos.c`, enable PC13 EXTI, USART2 for logging.

## Verify
- [ ] Button toggles LED via notification
- [ ] `ulTaskNotifyTake` blocks worker until press

## Modify
Pass press count as notification value:
```c
xTaskNotify(workerHandle, count, eSetValueWithOverwrite);
```

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 5  
**Level:** L3 RTOS (task notifications)

### Breakpoints
| Where | Why |
|-------|-----|
| `vTaskNotifyGiveFromISR` or EXTI path | ISR signals worker |
| `ulTaskNotifyTake` in worker | Blocks until notify |
| After take succeeds | Count decremented |

### Watch expressions
```
workerHandle
ulTaskNotifyValue(workerHandle)   // if API available; else step and watch locals
count
```

### Step drill
1. Worker blocked on `ulTaskNotifyTake` — Task List shows **Blocked**
2. Press button → ISR notify → **Resume** → worker **Ready**
3. **Step Over** `ulTaskNotifyTake` — returns with notification consumed

### Compare to semaphore
Same drill as Example 04 but **Expressions** show no separate semaphore object — notification lives in TCB.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Worker blocks without button | |
| One notify wakes worker per press | |
