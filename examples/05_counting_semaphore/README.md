# Example 05 — Counting Semaphore (Resource Pool)

**Day:** 7  
**Hardware:** USART2 @ 115200

---

## Theory

### Real-world analogy
Parking lot with **3 spaces**, **5 drivers** want to park:
- Driver takes slot → count goes 3→2→1→0
- 4th driver **waits** at gate
- Driver leaves → count++ → waiting driver enters

### API
```c
SemaphoreHandle_t pool = xSemaphoreCreateCounting(MAX_SLOTS, MAX_SLOTS);
xSemaphoreTake(pool, portMAX_DELAY);   // acquire slot (decrement)
xSemaphoreGive(pool);                  // release slot (increment)
```

### vs Mutex
- Mutex: one resource, ownership
- Counting sem: N identical resources, no ownership

---

## Practice

1. Enable USART2 + syscalls retarget (Example 03)
2. Copy `freertos.c` from this folder
3. Open serial 115200
4. Watch 5 workers compete for 3 slots

---

## Verify

| Check | Pass? |
|-------|-------|
| Max 3 ">>> IN section" at once | |
| Others print "waiting..." | |
| All workers eventually complete a cycle | |

---

## Modify

```c
#define MAX_SLOTS 1   // behaves like mutex
#define MAX_SLOTS 5   // no waiting — all run together
```

Simulate longer critical section:
```c
osDelay(2000);  // inside "IN section"
```
Queue of waiting workers becomes visible in UART.
