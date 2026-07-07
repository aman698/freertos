# FreeRTOS Practice — STM32F411RE (Basic + Advanced)

Complete hands-on curriculum: **20 days**, **13 examples**, **1 full capstone project**.

---

## Learning Paths

| Track | Guide | Days | Level |
|-------|-------|------|-------|
| **Basic** | [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md) | 1–10 | Tasks → mutex → timers |
| **Advanced** | [`ADVANCED_PRACTICE_GUIDE.md`](ADVANCED_PRACTICE_GUIDE.md) | 11–20 | Event groups → capstone |
| **Theory** | [`THEORY_REFERENCE.md`](THEORY_REFERENCE.md) | All | Deep concepts |
| **Interview Prep** | [`FREERTOS_INTERVIEW_PREP.md`](FREERTOS_INTERVIEW_PREP.md) | All | Oral questions + coding drills |
| **Embedded C** | [`c_practice/`](c_practice/) | 15 topics | C fundamentals for firmware |
| **DSA in C** | [`dsa_practice/`](dsa_practice/) | 10 topics | Data structures + algorithms |
| **Debugger** | [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md) | All | SWD/ST-LINK, step in/out, watch |
| **Config** | [`docs/FREERTOS_CONFIG_GUIDE.md`](docs/FREERTOS_CONFIG_GUIDE.md) | 11+ | CubeMX settings |

**Logs:** [`PRACTICE_LOG.md`](PRACTICE_LOG.md) | [`PRACTICE_LOG_ADVANCED.md`](PRACTICE_LOG_ADVANCED.md)

---

## Full Capstone Project (Day 20)

**[`projects/Advanced_FreeRTOS_Lab/`](projects/Advanced_FreeRTOS_Lab/)**

Modular production-style layout:
```
App/
  app_command.c   — Stream buffer CLI
  app_sensor.c    — Timer + queue
  app_events.c    — Event group + notifications
  app_monitor.c   — Stack/heap monitor
common/
  uart_debug.c    — Mutex-safe printf
  freertos_utils.c
```

---

## All Examples

### Basic (Days 1–10)
| # | Folder | Topic |
|---|--------|-------|
| 01 | `01_basic_multi_task` | Tasks, priorities, delay |
| 02 | `02_queue_button_led` | Queues + EXTI |
| 03 | `03_mutex_uart_printf` | Mutex |
| 04 | `04_timer_semaphore_isr` | Timer + semaphore |
| 05 | `05_counting_semaphore` | Resource pool |
| 06 | `06_stack_monitor` | Stack/heap |
| 07 | `07_uart_isr_queue` | UART ISR -> queue parser |

### Advanced (Days 11–20)
| # | Folder | Topic |
|---|--------|-------|
| 08 | `08_event_groups` | Multi-condition sync |
| 09 | `09_task_notifications` | Lightweight signals |
| 10 | `10_stream_buffer` | UART CLI |
| 11 | `11_queue_set` | Multiplexed queue wait |
| 12 | `12_deadlock_demo` | Inversion + deadlock |
| 13 | `13_static_allocation` | Static queues |
| **★** | `projects/Advanced_FreeRTOS_Lab` | **Full integrated project** |

---

## How to Practice (both sides)

### Theory side (before coding)
1. Read day section in `PRACTICE_GUIDE.md` or `ADVANCED_PRACTICE_GUIDE.md`
2. Read matching section in `THEORY_REFERENCE.md`
3. Read `examples/XX/README.md`
4. New to debugger? Read [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md) Part 1–3 first

### Code side (hands-on)
1. Create / reuse CubeMX project `FreeRTOS_Practice`
2. Copy `freertos.c` + `main_user_code.c` for that day
3. Advanced: add `common/*.c` and `app/*.c` modules
4. Build → **Debug (F11)** → run **Debugger Practice** in example README
5. Build → flash → verify checklist
6. Run **Modify** experiments in README
7. Fill practice log

### Files you edit in CubeIDE
```
Core/Src/freertos.c      ← main logic each day
Core/Src/main.c          ← USER CODE blocks only
Core/Src/uart_debug.c    ← common/ (Day 6+)
App/Src/*.c              ← capstone only
```

---

## Suggested Schedule

| Week | Days | Goal |
|------|------|------|
| 1 | 1–5 | Tasks, queues, semaphores |
| 2 | 6–10 | Mutex, timers, monitoring |
| 3 | 11–15 | Event groups, stream buffer, deadlock |
| 4 | 16–20 | DMA, static alloc, **capstone** |

---

## Board Pins (NUCLEO-F411RE)

| Pin | Use |
|-----|-----|
| PA5 | LD2 LED |
| PC13 | User button |
| PA2/PA3 | USART2 |

---

## Next Step

**Today:** Open [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md) Day 1 if new, or [`ADVANCED_PRACTICE_GUIDE.md`](ADVANCED_PRACTICE_GUIDE.md) Day 11 if basics done.

**End goal:** Complete [`projects/Advanced_FreeRTOS_Lab/README.md`](projects/Advanced_FreeRTOS_Lab/README.md) capstone.

**Interview goal:** Work through [`FREERTOS_INTERVIEW_PREP.md`](FREERTOS_INTERVIEW_PREP.md) and explain every synchronization choice without notes.
