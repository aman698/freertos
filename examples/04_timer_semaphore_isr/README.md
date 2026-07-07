# Example 04 — Software Timer + Binary Semaphore + ISR

**Days:** 5, 8, 9  
**Hardware:** PA5 LED, PC13 button EXTI

---

## Theory

### Software timer
- Created with `xTimerCreate(name, period, autoReload, id, callback)`
- Started with `xTimerStart(timer, blockTime)`
- Callback runs in **Timer Service Task** context (not ISR, not your task)
- Keep callback < 1 ms of work

### Binary semaphore in this example
- Timer: autonomous LED blink (no user task needed)
- Button ISR: `xSemaphoreGiveFromISR` wakes worker
- Worker: handles press (debounce, UART log)

### Combined learning
You practice **three mechanisms in one project**:
1. Periodic timing → timer
2. Event signal → semaphore
3. ISR deferral → GiveFromISR + task

---

## Practice — Step by Step

### 1. CubeMX
- `configUSE_TIMERS = 1`
- PA5 output, PC13 EXTI + NVIC EXTI15_10
- USART2 optional for worker messages
- Regenerate

### 2. Copy `freertos.c` + `main_user_code.c`

### 3. Day 5 only (semaphore focus)
Comment out timer create/start; toggle LED in worker on button.

### 4. Day 8 (full example)
Enable all timer code.

---

## Verify

| Check | Pass? |
|-------|-------|
| LED blinks every 500 ms without button | |
| Button press does not block blink | |
| Worker responds to each press | |

---

## Modify

| Experiment | What to learn |
|------------|---------------|
| `pdMS_TO_TICKS(100)` period | Faster blink |
| Remove `portYIELD_FROM_ISR` | Task may wait extra 1 tick |
| `osDelay(5000)` inside timer callback | Starves timer service |

---

## Architecture

```
xTimerCreate ──► BlinkTimerCallback ──► HAL_GPIO_TogglePin (500ms)

PC13 EXTI ──► GiveFromISR(buttonSem) ──► Worker Task ──► debounce + printf
```

---

## Debugger Practice

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) Part 5–6  
**Level:** L2–L3 (timer service + ISR + semaphore)

### Breakpoints
| Where | Why |
|-------|-----|
| Timer callback — `HAL_GPIO_TogglePin` | Runs in **Timer Service Task** context |
| EXTI / `GiveFromISR` path | ISR deferral |
| Worker task after `xSemaphoreTake` | Task woken by semaphore |

### Watch expressions
```
buttonSem
xTaskGetTickCount()
// Timer handle name from your freertos.c (e.g. blinkTimerHandle)
```

### Step drill — timer context
1. Breakpoint in timer **callback** (not `xTimerCreate`)
2. When hit, check **Call Stack** — parent is timer service task, not your worker
3. **Step Over** callback body — must stay short (theory: < 1 ms work)

### Step drill — ISR → semaphore
1. Breakpoint on `xSemaphoreGiveFromISR`
2. Press button → **Step Over** Give and `portYIELD_FROM_ISR`
3. **Resume** → worker task takes semaphore

### Theory check
**Step Into** `xTimerStart` from `MX_FREERTOS_Init` — initialization only; timer fires later in different context.

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| Timer callback hits every 500 ms without button | |
| Button hit runs ISR path then worker | |
| LED blink does not stop while stepping worker (Resume between presses) | |
