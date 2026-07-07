# Example 02 — Queue: Button → Debounce → LED

**Day:** 4 (queues), 9 (ISR review)  
**Hardware:** PA5 LED, PC13 button (EXTI)

---

## Theory

### Queue anatomy
```
[ msg3 ][ msg2 ][ msg1 ]  ← FIFO
  ↑ send          ↑ receive
```

- **Producer** sends data
- **Consumer** receives data
- **Blocking:** receiver waits if empty; sender waits if full

### Why two queues?
```
ISR ──► rawIsrQueue ──► debounce task ──► debouncedQueue ──► LED task
```

If we used one queue, the debounce task could accidentally read its own forwarded message. Two queues = clean pipeline.

### ISR vs task APIs
| Context | Send | Receive |
|---------|------|---------|
| Task | `xQueueSend` | `xQueueReceive` |
| ISR | `xQueueSendFromISR` | `xQueueReceiveFromISR` |

Always end ISR with `portYIELD_FROM_ISR(xHigherPriorityTaskWoken)`.

### Button on Nucleo
- PC13, **active LOW** (pressed = `GPIO_PIN_RESET`)
- Needs pull-up (CubeMX default)
- EXTI on **falling edge** = press detected

---

## Practice — Step by Step

### 1. CubeMX changes
1. PC13 → **GPIO_EXTI13**
2. GPIO mode: External Interrupt Mode with Falling edge
3. NVIC → **EXTI15_10 interrupt** → Enabled
4. Regenerate code

### 2. Replace `freertos.c`
Copy from `freertos.c` in this folder.

### 3. Add to `main.c` — USER CODE 0
From `main_user_code.c`:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_13) {
    Button_ISR_SendEventFromISR();
  }
}
```

### 4. Build → Flash → Press blue button

---

## Verify

| Check | Pass? |
|-------|-------|
| One press = one toggle | |
| Hold button → repeats after debounce | |
| LED does not flicker on single press | |

---

## Modify experiments

### A — Shrink queue
```c
#define RAW_QUEUE_LEN 1
```
Rapid clicks may drop events.

### B — Break debounce
```c
#define DEBOUNCE_MS 5
```
See mechanical bounce — multiple toggles.

### C — Trace with UART
In LED task:
```c
printf("Press #%lu\r\n", pressId);
```

---

## Data flow diagram

```
     ┌─────────┐   FromISR    ┌──────────────┐
     │  EXTI   │─────────────►│ rawIsrQueue  │
     │  ISR    │              └──────┬───────┘
     └─────────┘                     │ Receive
                                     ▼
                              ┌──────────────┐
                              │  Debounce    │
                              │  Task        │
                              └──────┬───────┘
                                     │ Send pressId
                                     ▼
                              ┌──────────────┐
                              │ debouncedQ   │
                              └──────┬───────┘
                                     │ Receive
                                     ▼
                              ┌──────────────┐
                              │  LED Task    │
                              │  Toggle PA5  │
                              └──────────────┘
```

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 5–6  
**Level:** L2 Intermediate (ISR + queues)

### Breakpoints
| Where | Why |
|-------|-----|
| `Button_ISR_SendEventFromISR` | ISR → queue path |
| `StartButtonDebounceTask` — after `xQueueReceive` | Consumer woke from ISR |
| `StartLedConsumerTask` — after `xQueueReceive` | Final pipeline stage |

### Watch expressions
```
pressId
uxQueueMessagesWaiting(rawIsrQueue)
uxQueueMessagesWaiting(debouncedQueue)
GPIOC->IDR & GPIO_PIN_13
```

### Step drill — ISR path
1. Resume; press blue button → halt in ISR function
2. **Step Over** `xQueueSendFromISR` → watch `uxQueueMessagesWaiting(rawIsrQueue)` increment
3. **Step Over** `portYIELD_FROM_ISR` → **Resume** → debounce task may run
4. In debounce task: **Step Into** `osDelay(DEBOUNCE_MS)` once to see blocking debounce

### Step drill — pipeline
1. Breakpoint after `pressId++` and `xQueueSend` to `debouncedQueue`
2. **Expressions:** `pressId` — conditional breakpoint `pressId == 3` (advanced)

### Theory check
- Why **Step Into** `HAL_GPIO_ReadPin` in task but only **Step Over** in ISR? (ISR time budget)

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| ISR fires once per press | |
| `rawIsrQueue` depth 0→1→0 after debounce reads | |
| `pressId` increments in LED task | |
