# FreeRTOS Practice — STM32F411RE + STM32CubeIDE

**Start here:** [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md) — full 10-day guide with **Theory + Practice** for each day.

**Track progress:** [`PRACTICE_LOG.md`](PRACTICE_LOG.md)

---

## What is in this repo?

| File / Folder | Purpose |
|---------------|---------|
| `PRACTICE_GUIDE.md` | Master guide — theory, steps, verify, modify per day |
| `PRACTICE_LOG.md` | Daily journal template |
| `examples/01..06/` | Complete code + per-example README |
| `examples/07_uart_isr_queue/` | Optional Day 9 UART challenge |

---

## Board pins (NUCLEO-F411RE)

| Pin | Function |
|-----|----------|
| PA5 | LD2 green LED |
| PC13 | User button (active low) |
| PA2/PA3 | USART2 TX/RX (115200) |

---

## How to practice (summary)

1. Create **one** CubeMX project: `FreeRTOS_Practice` (see PRACTICE_GUIDE setup)
2. Each day: read **Theory** → copy example files → **Verify** on board → **Modify**
3. Only edit inside `USER CODE BEGIN/END` blocks in CubeIDE
4. Fill `PRACTICE_LOG.md` after each session

---

## Example map

| Day | Topic | Folder |
|-----|-------|--------|
| 1–3 | Tasks, delay | `01_basic_multi_task` |
| 4 | Queues | `02_queue_button_led` |
| 6 | Mutex | `03_mutex_uart_printf` |
| 5,8,9 | Timer, sem, ISR | `04_timer_semaphore_isr` |
| 7 | Counting sem | `05_counting_semaphore` |
| 10 | Stack monitor | `06_stack_monitor` |

---

## Files to copy each day

```
CubeIDE project                    This repo
─────────────────────────────────  ─────────────────────────
Core/Src/freertos.c           ←    examples/XX/freertos.c
Core/Src/main.c (USER CODE)   ←    examples/XX/main_user_code.c
Core/Src/syscalls.c           ←    examples/03/syscalls_snippet.c (Day 6+)
```

---

## CubeMX FreeRTOS defaults

| Setting | Value |
|---------|-------|
| Interface | CMSIS_V2 |
| `configTOTAL_HEAP_SIZE` | 15360 |
| `configUSE_MUTEXES` | 1 |
| `configUSE_TIMERS` | 1 |
| `configCHECK_FOR_STACK_OVERFLOW` | 2 |

---

## Help

| Problem | Solution |
|---------|----------|
| Hard fault | Increase heap or task stack |
| Garbled UART | Use mutex (Example 03) |
| Button toggles 5× | Increase `DEBOUNCE_MS` |
| Task not running | Nothing blocking after `osKernelStart()` |

Full debugging and experiments: **PRACTICE_GUIDE.md**
