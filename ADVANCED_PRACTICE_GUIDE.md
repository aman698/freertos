# Advanced FreeRTOS Practice — Days 11–20 (STM32F411RE)

**Prerequisite:** Complete Days 1–10 in [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md)

**Goal:** Production-grade patterns — event groups, notifications, stream buffers, queue sets, DMA UART, deadlock awareness, and a **full capstone project**.

**Debugger:** Complete the **Debugger Practice** section in each example README. Master reference: [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md) (SWD/ST-LINK, JTAG theory, watch expressions, step in/out/return, FreeRTOS Task List, deadlock suspend).

---

## Advanced CubeMX Config (update before Day 11)

In `FreeRTOSConfig.h` (via CubeMX Config parameters or manual USER CODE in header):

```c
configUSE_TASK_NOTIFICATIONS       = 1
configUSE_EVENT_GROUPS             = 1
configUSE_STREAM_BUFFERS           = 1
configUSE_QUEUE_SETS               = 1
configUSE_TRACE_FACILITY           = 1
configUSE_STATS_FORMATTING_FUNCTIONS = 1
configCHECK_FOR_STACK_OVERFLOW     = 2
configTOTAL_HEAP_SIZE              = 24576   /* 24 KB for advanced labs */
```

Enable in CubeMX for capstone (Day 20):
- **TIM2** → PWM or periodic TRGO (optional)
- **ADC1** → Channel 5 on PA5 conflicts with LED — use **PA0** (A0 pin) for analog
- **DMA** → USART2 RX DMA circular (Day 17)

---

## Day 11 — Event Groups (Multi-Condition Sync)

### Theory
Event groups let one task wait until **multiple conditions** are true.

```
Task MAIN waits: BIT_SENSOR_READY | BIT_COMM_READY | BIT_CAL_DONE (wait ALL)
```

Unlike queue: no data payload — just bit flags.

**APIs:** `xEventGroupCreate`, `xEventGroupSetBits`, `xEventGroupWaitBits`, `xEventGroupClearBits`

### Practice
**Folder:** `examples/08_event_groups/`

Three init tasks each set one bit after random delay. Main task waits for all bits, then blinks LED fast 5×.

### Verify
- [ ] Main blocked until all 3 tasks complete
- [ ] UART shows order of bit sets

### Modify
- Change to `wait ANY bit` → main wakes on first task only
- Add timeout `pdMS_TO_TICKS(5000)` → handle `errEVENT_GROUP_WAIT_TIMEOUT`

---

## Day 12 — Task Notifications (Lightweight Signals)

### Theory
Direct notification to a specific task — **45% faster** than semaphore, less RAM.

```c
xTaskNotifyGive(receiverHandle);
ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // pdTRUE = clear count on exit
```

Limitation: **only one task** can be the receiver per notification index.

### Practice
**Folder:** `examples/09_task_notifications/`

Button ISR uses `vTaskNotifyGiveFromISR` instead of binary semaphore. Compare code size with Example 04.

### Verify
- [ ] Same button behavior as Day 5 semaphore version
- [ ] Fewer handles created (no semaphore object)

### Modify
- Use notification **value** as press count: `xTaskNotify(..., count, eSetValueWithOverwrite)`

---

## Day 13 — Stream Buffer (UART Byte Pipe)

### Theory
Stream buffer = continuous byte flow, **one writer + one reader**.

```
UART ISR (writer) ──stream──► Parser Task (reader)
```

More efficient than `xQueueSend` of single `uint8_t` (less overhead per byte).

### Practice
**Folder:** `examples/10_stream_buffer/`

ISR sends bytes to stream buffer; task reads line-oriented commands (`LED ON`, `LED OFF`).

### Verify
- [ ] Serial commands control LED
- [ ] Type `STATUS` → prints heap + stack

### Modify
- Reduce buffer to 16 bytes → see overflow behavior on long strings

---

## Day 14 — Queue Sets (Multiplexed Wait)

### Theory
`xQueueSelectFromSet(set, timeout)` blocks until **any** member queue has data.

Use case: one supervisor task handles button queue + UART queue + sensor queue.

### Practice
**Folder:** `examples/11_queue_set/`

Combine button events and UART commands in one dispatcher task.

### Verify
- [ ] Button and UART both handled without polling
- [ ] Dispatcher prints source of each event

---

## Day 15 — Priority Inversion & Deadlock Lab

### Theory

**Priority inversion:** Medium task blocks high task indirectly.

**Deadlock:** Task A holds M1 waits M2; Task B holds M2 waits M1.

### Practice
**Folder:** `examples/12_deadlock_demo/`

**Part A:** Demonstrate mutex inheritance (measure with GPIO toggle).

**Part B:** Intentional deadlock — detect with watchdog or timeout on `xSemaphoreTake`.

### Verify
- [ ] Part A: high task completes despite medium interference
- [ ] Part B: system hangs — you fix with lock ordering (`always take M1 then M2`)

### Modify
- Add `configUSE_MUTEXES` priority inheritance comment in code
- Fix deadlock using **consistent lock order**

---

## Day 16 — Runtime Stats & CPU Usage

### Theory
`vTaskGetRunTimeStats()` needs:
```c
configGENERATE_RUN_TIME_STATS = 1
configUSE_STATS_FORMATTING_FUNCTIONS = 1
portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
portGET_RUN_TIME_COUNTER_VALUE()
```

Uses a free hardware timer (e.g., TIM5 32-bit).

### Practice
**Folder:** `examples/06_stack_monitor/` + `common/freertos_utils.c`

Print per-task CPU % every 10 s.

### Verify
- [ ] Idle task % drops when you add busy-wait task
- [ ] Stats sum roughly to 100%

---

## Day 17 — DMA UART Ring Buffer + Stream Buffer

### Theory
```
DMA circular RX → idle interrupt → stream buffer → protocol task
```

CPU not involved per-byte — only on line complete or IDLE detected.

### Practice
**Folder:** `examples/07_uart_isr_queue/` (upgrade) + `common/uart_debug.c`

Implement ring buffer with `HAL_UARTEx_ReceiveToIdle_DMA`.

### Verify
- [ ] Flood UART at 115200 — no lost bytes
- [ ] CPU usage lower than byte-IRQ approach

---

## Day 18 — Memory Pools & Static Allocation

### Theory
**Dynamic** (`xQueueCreate`) — uses heap, can fragment.

**Static** (`xQueueCreateStatic`) — fixed buffers, deterministic.

```c
StaticQueue_t queueStruct;
uint8_t storage[LENGTH * ITEM_SIZE];
QueueHandle_t q = xQueueCreateStatic(LENGTH, ITEM_SIZE, storage, &queueStruct);
```

Production firmware often uses **static allocation** for certification (medical, automotive).

### Practice
**Folder:** `examples/13_static_allocation/`

Rewrite Example 02 queues as static.

### Verify
- [ ] `xPortGetFreeHeapSize()` unchanged after create
- [ ] Same functional behavior

---

## Day 19 — Tickless Idle & Low Power Preview

### Theory
When all tasks blocked, tickless stops SysTick, enters sleep, wakes on next event.

Requires correct `configEXPECTED_IDLE_TIME_BEFORE_SLEEP` tuning.

### Practice
1. Enable `configUSE_TICKLESS_IDLE` in CubeMX
2. Measure current with Nucleo (optional ammeter on 3.3V)
3. Observe longer sleep when only 1 s heartbeat runs

### Verify
- [ ] UART still works after wake
- [ ] Delays remain accurate within 1 tick

---

## Day 20 — CAPSTONE: Advanced FreeRTOS Lab (Full Project)

### What you build
Integrated system in `projects/Advanced_FreeRTOS_Lab/`:

```
┌─────────────┐     ┌──────────────┐     ┌─────────────┐
│ Sensor Task │────►│ Data Queue   │────►│ Process Task│
└─────────────┘     └──────────────┘     └──────┬──────┘
                                                │
┌─────────────┐     ┌──────────────┐            ▼
│ Button ISR  │────►│ Event Group  │◄─── Command Task (UART)
└─────────────┘     └──────────────┘
                           │
                    ┌──────▼──────┐
                    │ Monitor Task│──► stats UART
                    └─────────────┘
```

**Features combined:**
- Event groups for system ready
- Queues for sensor data
- Mutex for UART
- Task notifications for button
- Software timer for periodic sample
- Stream buffer for UART RX
- Stack + runtime monitor

### Practice
Follow `projects/Advanced_FreeRTOS_Lab/README.md` — full import guide.

### Verify (capstone checklist)
- [ ] `INIT` command prints system status
- [ ] `SAMPLE` triggers ADC read via queue
- [ ] Button sets event bit
- [ ] Monitor prints every 10 s
- [ ] No heap allocation after boot (static mode option)
- [ ] Explain every synchronization choice in 5 min oral review

---

## Advanced Example Index

| Day | Folder | Topic |
|-----|--------|-------|
| 11 | `08_event_groups` | Event groups |
| 12 | `09_task_notifications` | Task notify |
| 13 | `10_stream_buffer` | Stream buffer + CLI |
| 14 | `11_queue_set` | Queue set dispatcher |
| 15 | `12_deadlock_demo` | Inversion + deadlock |
| 16 | `06` + `common/` | Runtime stats |
| 17 | `07` + `common/uart_debug` | DMA UART |
| 18 | `13_static_allocation` | Static queues |
| 19 | CubeMX config | Tickless idle |
| 20 | `projects/Advanced_FreeRTOS_Lab` | **Full capstone** |

---

## Mastery Checklist (after Day 20)

- [ ] Draw memory map: heap, stacks, static buffers
- [ ] Implement ISR → deferred task without looking at notes
- [ ] Explain when **not** to use FreeRTOS (simple blink, hard real-time sub-10µs)
- [ ] Port one example to **static allocation only**
- [ ] Measure worst-case stack for every task
- [ ] Fix intentional deadlock in < 15 min

**Theory deep-dive:** [`THEORY_REFERENCE.md`](THEORY_REFERENCE.md)
