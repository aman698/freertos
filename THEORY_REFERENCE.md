# FreeRTOS Theory Reference — Complete Concept Guide

Deep reference for basic → advanced practice on STM32F411RE. Read sections matching your current day.

---

## 1. Kernel & Scheduler

### Preemptive vs Cooperative
| Mode | Behavior |
|------|----------|
| **Preemptive** (default) | Higher priority task runs immediately |
| **Cooperative** | Task must yield; rare on MCUs |

### Scheduler tick
- `configTICK_RATE_HZ = 1000` → 1 tick = 1 ms
- On each tick: check delays, timeouts, time slicing
- `pdMS_TO_TICKS(100)` converts ms → ticks safely

### Context switch cost
- Saves/restores registers + stack pointer
- Typical: 1–5 µs on Cortex-M4 @ 100 MHz
- **Lesson:** Frequent switching with tiny tasks wastes CPU

---

## 2. Tasks

### Task Control Block (TCB)
Kernel stores per task:
- Stack pointer
- Priority
- State (Running/Ready/Blocked/Suspended)
- Name (debug)

### Stack
- Grows downward on ARM
- Size in **words** in FreeRTOS APIs
- `uxTaskGetStackHighWaterMark()` → min free words ever
- Rule: measure under **worst-case** call depth (printf, sprintf, JSON)

### Task states diagram
```
                    osDelay/queue wait
    Running ──────────────────────────► Blocked
       ▲                                  │
       │         timeout/data ready       │
       └──────────────────────────────────┘
       
    Ready ◄─── scheduler picks when CPU free
```

### Anti-patterns
| Bad | Why |
|-----|-----|
| `while(1)` without block | 100% CPU burn |
| Task returns from function | Undefined — crash |
| Huge local arrays on stack | Stack overflow |
| `malloc` in tight loop | Heap fragmentation |

---

## 3. Queues

### Internal structure
- Ring buffer of **copied** items (not pointers by default)
- Send = memcpy into queue storage
- Separate mutex for queue structure integrity

### Blocking behavior
```c
xQueueSend(q, &data, 0);           // fail immediately if full
xQueueSend(q, &data, portMAX_DELAY); // block until space
xQueueReceive(q, &data, pdMS_TO_TICKS(100)); // 100ms timeout
```

### Queue sets (advanced)
- `xQueueCreateSet()` + `xQueueSelectFromSet()`
- One task waits on **multiple queues** simultaneously
- See Example 11

### ISR rules
```c
BaseType_t woken = pdFALSE;
xQueueSendFromISR(q, &item, &woken);
portYIELD_FROM_ISR(woken);
```

---

## 4. Semaphores

### Binary semaphore
- Count: 0 or 1
- **No ownership** — any task can Give
- Use: ISR → task signaling

### Counting semaphore
- Count: 0..N
- Use: resource pool (N buffers, N slots)

### Mutex (special semaphore)
- **Ownership** — only taker can give
- **Priority inheritance** — prevents priority inversion
- **Recursive mutex** optional (`xSemaphoreCreateRecursiveMutex`)

### Priority inversion (classic problem)
```
Low task L holds mutex
High task H waits on mutex → blocked
Medium task M runs (preempts L) → H starved by M
```
**Fix:** mutex priority inheritance boosts L to H's priority.

---

## 5. Task Notifications

- Each task has 32-bit notification value
- Faster and lighter than semaphore/queue
- `xTaskNotifyGive()` / `ulTaskNotifyTake()`
- **Indexed notifications** on newer FreeRTOS (task notification array)

### When to use
| Need | Use |
|------|-----|
| Signal only, one receiver | Task notification |
| Signal + data | Queue |
| Multiple waiters | Semaphore/queue |

See Example 09.

---

## 6. Event Groups

- Up to 24 event bits per group
- Wait for **any** or **all** of a bit mask
- `xEventGroupSetBits()`, `xEventGroupWaitBits()`

### Example pattern
```
Bit 0: WiFi connected
Bit 1: Sensor ready
Bit 2: Config loaded
Task waits: ALL_BITS before starting main loop
```

See Example 08.

---

## 7. Stream & Message Buffers

### Stream buffer
- Byte stream, single reader, single writer
- `xStreamBufferSend()` / `xStreamBufferReceive()`
- Perfect for UART byte pipe

### Message buffer
- Variable-length discrete messages
- `xMessageBufferSend()` with size header

See Example 10.

---

## 8. Software Timers

- Run in **Timer Service Task** (not ISR)
- Priority: `configTIMER_TASK_PRIORITY`
- Stack: `configTIMER_TASK_STACK_DEPTH`
- One-shot or auto-reload

### Callback rules
- Keep < 1 ms
- No blocking APIs (`vTaskDelay`, long `printf`)
- Can use `xTimerPendFunctionCall()` to defer heavy work to timer task via queue

---

## 9. Memory Management

### Heap schemes (FreeRTOS)
| Scheme | Free | Realloc | Fragmentation |
|--------|------|---------|---------------|
| heap_1 | No | No | None |
| heap_2 | Yes | No | Some |
| heap_3 | Wraps malloc | Yes | libc dependent |
| heap_4 | Yes | No | Coalesces adjacent |
| heap_5 | Yes | No | Multiple regions |

STM32Cube default: **heap_4**.

### Sizing formula (rough)
```
Heap = Σ task stacks (allocated from heap in dynamic create)
     + Σ queue storage (length × item size)
     + semaphores/mutexes (~80 bytes each)
     + 20% margin
```

### `configTOTAL_HEAP_SIZE`
If `xQueueCreate` returns NULL or `osThreadNew` fails → increase heap.

---

## 10. Interrupts & Cortex-M

### Priority numbering (ARM)
- **Lower number = higher logical priority**
- FreeRTOS syscall max priority: `configMAX_SYSCALL_INTERRUPT_PRIORITY`
- ISRs above this **must not** call FreeRTOS APIs

### NVIC config on STM32
```
Priority 0–4  : Cannot use FreeRTOS API (too high)
Priority 5–15 : Can use FromISR APIs (if configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY = 5)
```

### Deferred interrupt processing
```
ISR: clear flag, signal (queue/sem/notify), yield
Task: heavy processing, printf, protocol parsing
```

---

## 11. Tickless Idle

- `configUSE_TICKLESS_IDLE = 1`
- CPU sleeps in WFI/STOP between tasks
- Wakes on interrupt or next scheduled tick
- **Benefit:** lower power
- **Tradeoff:** timing granularity, debug complexity

See Example 12 notes in ADVANCED_PRACTICE_GUIDE.

---

## 12. Debugging & Asserts

**Hands-on guide:** [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md) — STM32CubeIDE, SWD/ST-LINK, step in/out, watch expressions, FreeRTOS views.

### On-chip debug (theory)

| Term | Meaning |
|------|---------|
| **SWD** | 2-wire ARM debug (SWDIO/SWCLK) — default on STM32 |
| **JTAG** | 4-wire legacy; same DAP, more pins |
| **ST-LINK** | USB bridge on Nucleo — flash + debug + virtual COM |
| **DAP** | Debug Access Port inside MCU — GDB talks through it |
| **Halt** | CPU frozen; inspect RAM/registers; ISRs do not run |
| **Resume** | Real-time execution; RTOS scheduler runs |

CubeMX **SYS → Debug → Serial Wire** keeps PA13/PA14 for SWD. If set to Disable, the debugger cannot attach.

### STM32CubeIDE stepping (theory)

| Action | Effect |
|--------|--------|
| **Step Over** | Execute one source line; callee runs to completion |
| **Step Into** | Enter function on current line (HAL, FreeRTOS, your code) |
| **Step Return** | Run until current function returns to caller |
| **Breakpoint** | Halt before line executes |

**FreeRTOS note:** Stepping in `osDelay` enters `vTaskDelay` — task moves to **Blocked** state; another task may run when you **Resume**.

### Runtime asserts & hooks

```c
configASSERT(x)  → trap on failure (halt in debugger)
configCHECK_FOR_STACK_OVERFLOW = 2
vApplicationStackOverflowHook()
vApplicationMallocFailedHook()
```

Set breakpoint in overflow hook; inspect `pcTaskName` and `uxTaskGetStackHighWaterMark(xTask)`.

### Useful APIs (call from Expressions while halted)

```c
uxTaskGetStackHighWaterMark(NULL)
xPortGetFreeHeapSize()
xPortGetMinimumEverFreeHeapSize()
uxQueueMessagesWaiting(queueHandle)
vTaskList(buffer)
vTaskGetRunTimeStats(buffer)  // needs configGENERATE_RUN_TIME_STATS
```

### FreeRTOS debug config

```
configUSE_TRACE_FACILITY = 1     // Task List view in CubeIDE
configCHECK_FOR_STACK_OVERFLOW = 2
configASSERT( ( x ) )             // defined in FreeRTOSConfig.h
```

### Common fault causes (debugger investigation)

| Fault location | Likely cause |
|----------------|--------------|
| `prvTaskExitError` | Task returned — missing `for(;;)` |
| Inside `FromISR` API from task | Wrong API variant |
| `printf` / deep call stack | Stack size too small |
| `xQueueSend` with NULL handle | Create failed or wrong scope |
| Hang, no fault | Deadlock — Suspend CPU, check Task List **Blocked** tasks |

### Watch expression examples

```c
xTaskGetTickCount()
GPIOC->IDR & GPIO_PIN_13          // button state
uxQueueMessagesWaiting(rawIsrQueue)
xSemaphoreGetMutexHolder(uartMutex) // NULL = not held
```

---

## 13. CMSIS-RTOS v2 vs Native API

| CMSIS | Native FreeRTOS |
|-------|-----------------|
| `osThreadNew` | `xTaskCreate` |
| `osMessageQueuePut` | `xQueueSend` |
| `osMutexAcquire` | `xSemaphoreTake` |
| `osEventFlagsSet` | `xEventGroupSetBits` |

CubeMX generates CMSIS wrappers. Native API always available by including `task.h`, `queue.h`.

---

## 14. API Selection Cheat Sheet

| Problem | Best API |
|---------|----------|
| Pass struct between tasks | Queue |
| ISR signals task | Queue FromISR, semaphore GiveFromISR, or TaskNotify |
| Protect UART | Mutex |
| N identical buffers | Counting semaphore |
| Wait for 3 conditions | Event group |
| Byte stream UART | Stream buffer |
| Fast 1:1 signal | Task notification |
| Wait on 3 queues | Queue set |
| Periodic 50 ms job | Software timer |
| Strict 1 kHz control loop | Task + `vTaskDelayUntil` |

---

## 15. Common Interview / Exam Topics

1. Why not spin-wait on flag? → wastes CPU, blocks low-priority work
2. Mutex vs binary semaphore? → ownership + inheritance
3. What happens if queue full? → send blocks or times out
4. Can two tasks share a queue handle? → yes, handle is safe
5. Maximum ISR work? → clear source, signal, < few µs

---

**Next:** [`ADVANCED_PRACTICE_GUIDE.md`](ADVANCED_PRACTICE_GUIDE.md) for Days 11–20 hands-on labs.
