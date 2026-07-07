# FreeRTOS Full Practice Guide — Theory + Code (STM32F411RE)

**How to use this guide:** Each day has four blocks. Read **Theory** first, then follow **Practice** step-by-step in STM32CubeIDE, **Verify** on hardware, then **Modify** to deepen understanding.

**Board:** NUCLEO-F411RE | **IDE:** STM32CubeIDE | **RTOS:** FreeRTOS CMSIS_V2

---

## One-Time Setup (Do Once Before Day 1)

### Step A — Create base project

1. Open STM32CubeIDE → **File → New → STM32 Project**
2. **Board Selector** → search `NUCLEO-F411RE` → Next → name project `FreeRTOS_Practice` → Finish
3. Say **Yes** to initialize peripherals

### Step B — CubeMX pin & clock config

| Peripheral | Setting |
|------------|---------|
| **SYS → Debug** | Serial Wire |
| **RCC → HSE** | BYPASS (8 MHz from ST-LINK) |
| **FREERTOS** | Enabled, Interface: **CMSIS_V2** |
| **PA5** | GPIO_Output (LD2 LED) |
| **PC13** | GPIO_EXTI13, Pull-up, Falling edge trigger (Days 4+) |
| **USART2** | Async 115200 8N1 (Days 3, 6, 10) |
| **NVIC → EXTI15_10** | Enabled (Days 4+) |

### Step C — FreeRTOS advanced settings

Open **FreeRTOS → Config parameters** and set:

```
configTOTAL_HEAP_SIZE        = 15360
configUSE_MUTEXES            = 1
configUSE_TIMERS             = 1
configUSE_TRACE_FACILITY     = 1
configCHECK_FOR_STACK_OVERFLOW = 2
```

### Step D — Generate and test

1. **Project → Generate Code**
2. Build (hammer icon) → Run (play icon)
3. LED should do nothing yet — that is OK. Toolchain works.

### Step E — Debugger setup (do once; practice every day)

**Full guide:** [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md)

| Topic | Setting / action |
|-------|------------------|
| CubeMX debug | **SYS → Debug → Serial Wire** (already in Step B) |
| Launch | **Run → Debug (F11)** — downloads firmware and halts CPU |
| Step controls | F6 Over, F5 Into, F7 Return, F8 Resume |
| Watch | **Window → Show View → Expressions** |
| RTOS | `configUSE_TRACE_FACILITY = 1` → **FreeRTOS Task List** view |

**Day 1 minimum drill:** After flashing Example 01, set breakpoint in `StartLedTask` → F11 → F6 step through `HAL_GPIO_TogglePin` and `osDelay` → open Task List → see `ledTask` **Blocked** during delay.

Each example README has a **Debugger Practice** section — complete it the same day as the code lab.

### Files you will edit every day

| File | What you change |
|------|-----------------|
| `Core/Src/freertos.c` | Tasks, queues, semaphores, timers |
| `Core/Src/main.c` | `USER CODE` blocks, EXTI callback |
| `Core/Src/syscalls.c` | `printf` retarget (Day 6+) |
| `Core/Inc/FreeRTOSConfig.h` | Only if guide says so |

**Rule:** Never edit code outside `USER CODE BEGIN/END` blocks in generated files — CubeMX will overwrite your changes on re-generate.

---

## Day 1 — Why FreeRTOS? First Task

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Scheduler** | Kernel picks which task runs on CPU |
| **Task** | Independent thread with its own stack |
| **Tick** | System heartbeat, default 1 ms (`configTICK_RATE_HZ = 1000`) |
| **Blocking** | `osDelay()` puts task to sleep; CPU runs other tasks |
| **Bare-metal problem** | One `while(1)` with multiple jobs = messy timing |

**Key APIs:** `osThreadNew()`, `osDelay()`, `osKernelStart()`

**Flow:**
```
main() → HAL_Init() → MX_*_Init() → osKernelInitialize()
      → MX_FREERTOS_Init() [create tasks]
      → osKernelStart() [scheduler takes over — never returns]
```

### Practice (30 min)

**Folder:** `examples/01_basic_multi_task/`

1. Open `Core/Src/freertos.c` in your CubeIDE project
2. Copy content from `examples/01_basic_multi_task/freertos.c` into `freertos.c` (replace or merge `USER CODE` sections)
3. Copy `main_user_code.c` snippets into matching `USER CODE` blocks in `main.c`
4. Build and flash

**What you type yourself (minimum):**
- `osThreadNew(StartLedTask, ...)`
- `for(;;) { HAL_GPIO_TogglePin(...); osDelay(200); }`

### Verify

- [ ] Green LED (LD2) blinks ~every 200 ms
- [ ] Debugger: **Window → Show View → FreeRTOS Task List** shows `ledTask` and `heartbeatTask`

### Modify (experiments)

| Change | Expected result |
|--------|-----------------|
| `osDelay(200)` → `osDelay(1000)` | Slower blink |
| Remove `heartbeatTask` | Still blinks — one task is enough |
| Use `HAL_Delay(200)` instead of `osDelay` | Blocks entire scheduler — bad practice |

### Practice log (write 2 lines)

> Today I learned that `osKernelStart()` never returns because _______

---

## Day 2 — Priorities & Preemption

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Preemption** | Higher priority task interrupts lower priority immediately |
| **Ready state** | Task can run but waits for CPU |
| **Blocked state** | Task waits on delay/queue/semaphore — not using CPU |
| **Starvation** | Low task never runs if high task never blocks |

**CMSIS priorities (higher number = more important):**
`osPriorityIdle` < `osPriorityLow` < `osPriorityBelowNormal` < `osPriorityNormal` < `osPriorityAboveNormal` < `osPriorityHigh`

**Rule:** Equal priority tasks share CPU via **time slicing** (round-robin each tick).

### Practice (30 min)

Still in **Example 1** — enable USART2 in CubeMX if not done.

1. Add `retarget printf` from `examples/03_mutex_uart_printf/syscalls_snippet.c` into `syscalls.c`
2. In `StartHeartbeatTask`, uncomment/add:
   ```c
   printf("[heartbeat] prio=BelowNormal\r\n");
   ```
3. Add a third task `urgentTask` at `osPriorityHigh` printing every 100 ms
4. Open serial terminal: 115200 baud on ST-LINK COM port

### Verify

- [ ] `[urgent]` messages appear much more often than `[heartbeat]`
- [ ] LED still blinks — high-priority task uses `osDelay`, so others get CPU

### Modify

| Change | Expected result |
|--------|-----------------|
| Set `urgentTask` to `osPriorityNormal` (same as LED) | Both share CPU evenly |
| Remove all `osDelay` from `urgentTask` | **Starvation** — LED/heartbeat may freeze |

---

## Day 3 — Precise Timing with `vTaskDelayUntil`

### Theory (10 min)

| API | Use case |
|-----|----------|
| `vTaskDelay(n)` | Delay **n ticks from now** — drift accumulates |
| `vTaskDelayUntil(&last, n)` | Wake at **fixed absolute intervals** — no drift |

**Example:** 300 ms period — `vTaskDelayUntil` keeps exact 300 ms even if work takes 5 ms.

```c
TickType_t last = xTaskGetTickCount();
for (;;) {
    do_work();
    vTaskDelayUntil(&last, pdMS_TO_TICKS(300));
}
```

### Practice (30 min)

Edit `StartLedTask` in `freertos.c`:

```c
void StartLedTask(void *argument) {
  TickType_t lastWake = xTaskGetTickCount();
  for (;;) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(300));
  }
}
```

Add second timing in `heartbeatTask` with 700 ms using `vTaskDelayUntil`. Print tick count:

```c
printf("tick=%lu\r\n", (unsigned long)xTaskGetTickCount());
```

### Verify

- [ ] LED period stable at 300 ms (measure with phone stopwatch or logic analyzer)
- [ ] `tick` value increments by ~700 between heartbeat prints

### Modify

| Change | Expected result |
|--------|-----------------|
| Add 50 ms fake work before `vTaskDelayUntil` | Period still 300 ms (unlike `vTaskDelay`) |
| Switch to `osDelay(300)` | Period becomes 350 ms (300 + 50 work) — **drift** |

---

## Day 4 — Queues (Producer → Consumer)

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Queue** | FIFO buffer safe between tasks/ISR |
| **Send** | `xQueueSend()` — blocks if queue full (unless timeout 0) |
| **Receive** | `xQueueReceive()` — blocks if queue empty |
| **Depth** | Max messages; small depth → `errQUEUE_FULL` |

**Why queues?** Passing an `int` via global variable is **not thread-safe** without protection.

**Data flow for Example 2:**
```
Button press → EXTI ISR → rawIsrQueue → debounce task → debouncedQueue → LED task
```

### Practice (45 min)

**Folder:** `examples/02_queue_button_led/`

1. CubeMX: enable PC13 EXTI + NVIC EXTI15_10 → regenerate
2. Replace `freertos.c` with example 2 code
3. Paste EXTI callback from `main_user_code.c` into `main.c` `USER CODE 0`
4. Build, flash

Read `examples/02_queue_button_led/README.md` for line-by-line explanation.

### Verify

- [ ] Each button press toggles LED once (not 3–5 times from bounce)
- [ ] Rapid presses: LED keeps up; extra events dropped if queue full

### Modify

| Change | Expected result |
|--------|-----------------|
| `RAW_QUEUE_LEN` = 1 | Still works for slow pressing |
| `DEBOUNCE_MS` = 5 | Multiple toggles per press (bounce) |
| Send from task instead of ISR | Works without `FromISR` — compare APIs |

---

## Day 5 — Binary Semaphores

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Binary semaphore** | Signal event (0 or 1). No ownership. |
| **Take** | `xSemaphoreTake` — waits until given |
| **Give** | `xSemaphoreGive` — wakes waiting task |
| **vs Queue** | Semaphore = signal only; queue = signal + data |

**ISR rule:** Only `xSemaphoreGiveFromISR()` in interrupt — never `Give()`.

### Practice (30 min)

**Folder:** `examples/04_timer_semaphore_isr/` (semaphore part only)

1. Copy Example 4 `freertos.c` but **comment out** timer code temporarily
2. Keep `buttonSem` + `StartWorkerTask` + `Button_ISR_GiveSemFromISR`
3. In worker: toggle LED on each semaphore take

### Verify

- [ ] Press button → LED toggles (via task, not ISR)
- [ ] ISR is short (no delay in callback)

### Modify

| Change | Expected result |
|--------|-----------------|
| Double-press fast | Second may be missed (binary sem has no count) — learn limit |
| Replace with `xTaskNotifyGive()` | Same pattern, less RAM |

---

## Day 6 — Mutexes (Shared UART)

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Mutex** | Mutual exclusion — only one owner at a time |
| **Ownership** | Task that `Take`s must `Give` back |
| **Priority inheritance** | Low task holding mutex boosts priority if high task waits |
| **vs Binary sem** | Never use binary sem for mutual exclusion |

**Problem:** `printf` uses internal buffer → two tasks → garbled bytes on UART.

### Practice (45 min)

**Folder:** `examples/03_mutex_uart_printf/`

1. CubeMX: USART2 115200 → regenerate
2. Add `syscalls_snippet.c` code to `syscalls.c`
3. Replace `freertos.c` with example 3
4. Flash, open serial 115200

### Verify

- [ ] `[FAST]` and `[SLOW]` lines are complete, not mixed
- [ ] Comment out mutex `Take/Give` → **garbled output** (proves why mutex needed)

### Modify

| Change | Expected result |
|--------|-----------------|
| `xSemaphoreTake` timeout = 10 ms, hold mutex 500 ms | `SafePrintf` drops messages after timeout |
| One task only | Mutex unnecessary — but good habit |

---

## Day 7 — Counting Semaphore (Resource Pool)

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Counting semaphore** | Counts N available slots |
| **Create** | `xSemaphoreCreateCounting(max, initial)` |
| **Use** | Take = acquire slot; Give = release slot |

**Real use:** 3 DMA buffers, 5 tasks producing data — only 3 run at once.

### Practice (45 min)

**Folder:** `examples/05_counting_semaphore/`

1. Copy `freertos.c` into project
2. Five worker tasks compete for 3 slots
3. Watch UART: only 3 workers run concurrently

### Verify

- [ ] UART shows max 3 workers "in critical section" at same time
- [ ] Others print "waiting for slot"

### Modify

| Change | Expected result |
|--------|-----------------|
| `MAX_SLOTS` = 1 | Pure mutex-like behavior |
| `MAX_SLOTS` = 5 | All workers run together |

---

## Day 8 — Software Timers

### Theory (10 min)

| Concept | Meaning |
|---------|---------|
| **Software timer** | Callback at interval without dedicated task |
| **Timer service task** | FreeRTOS internal task runs callbacks |
| **One-shot vs auto-reload** | `pdFALSE` / `pdTRUE` last param in `xTimerCreate` |
| **RAM saving** | Timer uses less RAM than `osThreadNew` for simple periodic jobs |

**Warning:** Timer callback is **not ISR** but should still be short — no `vTaskDelay`.

### Practice (45 min)

**Folder:** `examples/04_timer_semaphore_isr/` (full example)

1. Enable `configUSE_TIMERS = 1` in CubeMX
2. Use full Example 4 code — timer blinks LED, button wakes worker
3. Compare: disable timer, use LED task with `osDelay(500)` — note RAM in `.map` file

### Verify

- [ ] LED blinks every 500 ms automatically
- [ ] Button press handled by worker task (check UART if enabled)

### Modify

| Change | Expected result |
|--------|-----------------|
| Timer period 100 ms | Faster blink |
| Long `osDelay(2000)` inside timer callback | Delays other timers — **bad practice demo** |

---

## Day 9 — ISR Rules & Deferred Processing

### Theory (10 min)

| Rule | Reason |
|------|--------|
| ISR must be short | Hardware may miss next interrupt |
| Use `...FromISR()` APIs | Regular APIs may corrupt kernel state |
| Call `portYIELD_FROM_ISR()` | Wake higher-priority task immediately |
| No `printf`, `malloc`, `vTaskDelay` in ISR | Too slow / not ISR-safe |

**Pattern:** ISR → queue/semaphore → task does heavy work.

### Practice (30 min)

Review Example 2 and 4 side by side. Fill this table from your code:

| Location | API used | Safe? |
|----------|----------|-------|
| `HAL_GPIO_EXTI_Callback` | `xQueueSendFromISR` | Yes |
| `StartWorkerTask` | `xSemaphoreTake` | Yes |
| EXTI callback | `HAL_Delay(50)` | **NO** |

**Optional challenge:** Add UART RX interrupt → queue → echo task (outline in `examples/07_uart_isr_queue/README.md`).

### Verify

- [ ] You can explain aloud why Example 2 uses two queues
- [ ] You can draw ISR → task diagram on paper

---

## Day 10 — Stack, Heap & Production Habits

### Theory (10 min)

| Tool | Purpose |
|------|---------|
| `uxTaskGetStackHighWaterMark()` | Minimum free stack words — **low = danger** |
| `configTOTAL_HEAP_SIZE` | All tasks/queues allocated from here |
| `configCHECK_FOR_STACK_OVERFLOW` | Trap on overflow |
| `vTaskList()` | Text snapshot of all tasks (needs `configUSE_TRACE_FACILITY`) |

**Typical stack sizes on F411:**
- Simple GPIO task: 256 words (1 KB)
- `printf` task: 512+ words (2 KB+)

### Practice (45 min)

**Folder:** `examples/06_stack_monitor/`

1. Add monitor task from example 6 to any project with 2+ tasks
2. Every 10 s print stack high-water mark for each task
3. Enable `configCHECK_FOR_STACK_OVERFLOW = 2` in `FreeRTOSConfig.h`

### Verify

- [ ] High-water mark > 50 words for each task
- [ ] Deliberately reduce `stack_size` to 64 → overflow hook or hard fault (then restore!)

### Final review checklist

- [ ] Explain difference: queue vs binary sem vs mutex
- [ ] Write ISR-safe send in one line from memory
- [ ] Know where heap size is configured
- [ ] Re-build Example 2 from scratch in < 30 min

---

## Quick Reference Card

```
Create task     osThreadNew(func, NULL, &attr)
Delay           osDelay(ms)  or  vTaskDelay(pdMS_TO_TICKS(ms))
Queue           xQueueCreate(len, sizeof(item))
                xQueueSend / xQueueReceive
ISR queue       xQueueSendFromISR + portYIELD_FROM_ISR
Mutex           xSemaphoreCreateMutex + Take/Give
Binary sem      xSemaphoreCreateBinary
Counting sem    xSemaphoreCreateCounting(max, initial)
Timer           xTimerCreate + xTimerStart
Stack check     uxTaskGetStackHighWaterMark(NULL)
```

---

## Example Index

| Day | Folder | Files to copy |
|-----|--------|---------------|
| 1–3 | `01_basic_multi_task/` | `freertos.c`, `main_user_code.c` |
| 4 | `02_queue_button_led/` | `freertos.c`, `main_user_code.c` |
| 6 | `03_mutex_uart_printf/` | `freertos.c`, `syscalls_snippet.c` |
| 5,8,9 | `04_timer_semaphore_isr/` | `freertos.c`, `main_user_code.c` |
| 7 | `05_counting_semaphore/` | `freertos.c` |
| 10 | `06_stack_monitor/` | `freertos_additions.c` |

**Daily log template:** `PRACTICE_LOG.md`

---

## Continue to Advanced Track (Days 11–20)

After completing Day 10:

- **[ADVANCED_PRACTICE_GUIDE.md](ADVANCED_PRACTICE_GUIDE.md)** — event groups, notifications, stream buffers, deadlock, capstone
- **[THEORY_REFERENCE.md](THEORY_REFERENCE.md)** — full concept deep-dive
- **[projects/Advanced_FreeRTOS_Lab/](projects/Advanced_FreeRTOS_Lab/)** — Day 20 modular full project
- **[PRACTICE_LOG_ADVANCED.md](PRACTICE_LOG_ADVANCED.md)** — advanced daily journal
