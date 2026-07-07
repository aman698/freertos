# Advanced FreeRTOS Lab — Full Capstone Project (Day 20)

**This is the complete integrated project** combining all advanced patterns.

---

## What You Build

A mini firmware "platform" with:

| Module | File | Sync mechanism |
|--------|------|----------------|
| UART CLI | `app_command.c` | Stream buffer + mutex printf |
| Sensor sim | `app_sensor.c` | Queue + software timer |
| System events | `app_events.c` | Event group |
| Button | `app_events.c` | Task notification |
| Monitor | `app_monitor.c` | Periodic task, stack/heap report |
| Init | `freertos.c` | Creates all objects |

---

## Architecture

```
                    ┌─────────────────────────────────────┐
                    │         app_events (EventGroup)      │
                    │  BIT_BTN | BIT_SENSOR | BIT_COMM    │
                    └───────────────┬─────────────────────┘
                                    │
     PC13 EXTI ──notify──► btn ─────┤
                                    │
     TIM sensor ──queue──► sensor ───┤──► processTask
                                    │
     UART stream ──► command ────────┘

     monitorTask ──► UART stats every 10s
```

---

## CubeMX Setup (complete)

| Item | Config |
|------|--------|
| Board | NUCLEO-F411RE |
| FREERTOS | CMSIS_V2, heap 24KB |
| PA5 | GPIO_Output (LED) |
| PC13 | EXTI13 falling |
| USART2 | 115200, **RX interrupt enabled** |
| NVIC | EXTI15_10 enabled |
| ADC1 | Optional IN0 on PA0 for real sensor (or use simulated) |

### FreeRTOS config (must enable)
```
configUSE_TASK_NOTIFICATIONS = 1
configUSE_EVENT_GROUPS = 1
configUSE_STREAM_BUFFERS = 1
configUSE_TIMERS = 1
configUSE_MUTEXES = 1
configUSE_TRACE_FACILITY = 1
configCHECK_FOR_STACK_OVERFLOW = 2
configTOTAL_HEAP_SIZE = 24576
```

---

## Import Steps (Full Project)

### 1. Create CubeMX project `Advanced_FreeRTOS_Lab`

Generate code once.

### 2. Copy shared drivers

| From repo | To CubeIDE project |
|-----------|-------------------|
| `common/uart_debug.c` | `Core/Src/uart_debug.c` |
| `common/uart_debug.h` | `Core/Inc/uart_debug.h` |
| `common/freertos_utils.c` | `Core/Src/freertos_utils.c` |
| `common/freertos_utils.h` | `Core/Inc/freertos_utils.h` |

**Add to build:** Right-click project → Refresh (auto-detects new .c files)

### 3. Copy application modules

| From repo | To CubeIDE project |
|-----------|-------------------|
| `projects/Advanced_FreeRTOS_Lab/app/*.c` | `App/Src/` (create folder) |
| `projects/Advanced_FreeRTOS_Lab/app/*.h` | `App/Inc/` |
| `projects/Advanced_FreeRTOS_Lab/freertos.c` | Merge into `Core/Src/freertos.c` USER CODE |
| `projects/Advanced_FreeRTOS_Lab/main_user_code.c` | Paste into `main.c` USER CODE |

### 4. Include paths

Project Properties → C/C++ Build → Settings → MCU GCC Compiler → Include paths:
```
../App/Inc
```

### 5. Build → Flash → Serial 115200

---

## UART Commands (Capstone CLI)

| Command | Action |
|---------|--------|
| `HELP` | List commands |
| `STATUS` | Heap, stack, event bits |
| `SAMPLE` | Trigger sensor sample |
| `LED ON` / `LED OFF` | Control LD2 |
| `TASKS` | Print `vTaskList` |

---

## Verify Checklist

- [ ] Boot messages show init sequence
- [ ] Event group: all bits set before "SYSTEM READY"
- [ ] Button press sets `BIT_BTN` and toggles LED
- [ ] `SAMPLE` prints sensor value (simulated counter)
- [ ] Monitor prints every 10 s
- [ ] `TASKS` shows all task states
- [ ] No hard fault for 30 min run

---

## Practice Exercises (after capstone works)

1. **Add command `RATE 500`** — change sensor timer period at runtime
2. **Add ADC** — replace simulated value with `HAL_ADC_Read`
3. **Static allocation** — convert sensor queue to `xQueueCreateStatic`
4. **Remove event group** — refactor to pure queues (understand tradeoff)
5. **Measure stack** — reduce stacks until overflow, document HWM

---

## Oral Exam (5 min — explain aloud)

1. Why stream buffer for UART but queue for sensor data?
2. Why mutex around printf but not around GPIO toggle?
3. What happens if monitor task stack is 128 words?
4. Draw ISR → deferred processing path for button.

---

## Debugger Practice (Capstone)

**Guide:** [`docs/DEBUGGING_GUIDE.md`](../../docs/DEBUGGING_GUIDE.md) — full L1–L5 curriculum  
**Level:** L4–L5 Expert integration

### System map — where to break

| Module | Function / line | Teaches |
|--------|-----------------|---------|
| `app_events.c` | EXTI / notify | ISR → notification |
| `app_sensor.c` | timer callback | Timer service context |
| `app_command.c` | stream receive | Byte stream CLI |
| `freertos.c` | `processTask` wait on event group | Multi-bit sync |
| `app_monitor.c` | 10 s report | Periodic + HWM |

### Watch panel (save as Expression group)
```
xPortGetFreeHeapSize()
xEventGroupGetBits(xEventGroupHandle)
uxTaskGetStackHighWaterMark(NULL)
GPIOC->IDR & GPIO_PIN_13
```

### Step drill — boot sequence
1. Break on `xEventGroupWaitBits` in process task — **Blocked** until SENSOR + COMM + BTN bits
2. **Resume** as subsystems start — watch bits in Expressions
3. Type `STATUS` in UART — break in command parser — **Step Through** status print

### Step drill — cross-module
1. Press button → break in event path → **Step Return** to ISR → **Resume**
2. `processTask` wakes — **Step Over** LED / event handling
3. `SAMPLE` command → sensor queue → process task receive

### Advanced sessions

| Session | Technique |
|---------|-----------|
| **Deadlock hunt** | Suspend on intentional bug; Task List + Call Stack |
| **Stack budget** | Shrink `processTask` stack; overflow hook + `pcTaskName` |
| **Timing** | DWT `CYCCNT` around sensor path ([`DEBUGGING_GUIDE`](../../docs/DEBUGGING_GUIDE.md) Part 7) |
| **Live queue depth** | Live expression on sensor queue waiting count during `SAMPLE` spam |

### Verify (debugger)
| Check | Pass? |
|-------|-------|
| All tasks visible in Task List | |
| Event bits match UART `STATUS` | |
| Button path ISR → task without fault | |
| 30 min run: no drift in heap Expressions | |

---

## File List

```
projects/Advanced_FreeRTOS_Lab/
├── README.md           (this file)
├── freertos.c          (init + process task)
├── main_user_code.c
└── app/
    ├── app_config.h    (shared defines)
    ├── app_events.c/h
    ├── app_sensor.c/h
    ├── app_command.c/h
    └── app_monitor.c/h
```
