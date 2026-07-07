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
