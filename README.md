# Embedded Automotive BSP Developer Prep — STM32F411RE

Full interview-prep system: **embedded C**, **DSA**, **FreeRTOS**, **automotive protocols (CAN/J1939/ISO-TP/UDS)**, and hardware integration on a NUCLEO-F411RE.

**New here? Start at [`MASTER_STUDY_PLAN.md`](MASTER_STUDY_PLAN.md)** — it sequences everything below into a 10-week program and is the single source of truth for "what do I do next."

---

## Learning Paths

| Track | Guide | Scope | Level |
|-------|-------|-------|-------|
| **Master Plan** | [`MASTER_STUDY_PLAN.md`](MASTER_STUDY_PLAN.md) | Weeks 1–10 | Sequences every track below |
| **Embedded C** | [`c_practice/`](c_practice/) | 15 topics, 180 programs | C fundamentals for firmware |
| **DSA in C** | [`dsa_practice/`](dsa_practice/) | 10 topics, 100 programs | Data structures + algorithms |
| **FreeRTOS Basic** | [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md) | Days 1–10 | Tasks → mutex → timers |
| **FreeRTOS Advanced** | [`ADVANCED_PRACTICE_GUIDE.md`](ADVANCED_PRACTICE_GUIDE.md) | Days 11–20 | Event groups → capstone |
| **FreeRTOS Theory** | [`THEORY_REFERENCE.md`](THEORY_REFERENCE.md) | All | Deep concepts |
| **FreeRTOS Interview Prep** | [`FREERTOS_INTERVIEW_PREP.md`](FREERTOS_INTERVIEW_PREP.md) | All | Oral questions + coding drills |
| **Automotive Protocols** | [`automotive_protocols/`](automotive_protocols/) | 7 topics, ~72 programs | UART/SPI/I2C → CAN → J1939 → ISO-TP → UDS |
| **Automotive Interview Prep** | [`AUTOMOTIVE_INTERVIEW_PREP.md`](AUTOMOTIVE_INTERVIEW_PREP.md) | All | Oral questions + coding drills |
| **Hardware Integration** | [`examples/14_stm32_can_bxcan/`](examples/14_stm32_can_bxcan/) | Day 10 (protocol plan) | bxCAN ISR → J1939 decode task |
| **Debugger** | [`docs/DEBUGGING_GUIDE.md`](docs/DEBUGGING_GUIDE.md) | All | SWD/ST-LINK, step in/out, watch |
| **Config** | [`docs/FREERTOS_CONFIG_GUIDE.md`](docs/FREERTOS_CONFIG_GUIDE.md) | 11+ | CubeMX settings |

**Logs:** [`PRACTICE_LOG.md`](PRACTICE_LOG.md) | [`PRACTICE_LOG_ADVANCED.md`](PRACTICE_LOG_ADVANCED.md) | [`automotive_protocols/PRACTICE_LOG_PROTOCOLS.md`](automotive_protocols/PRACTICE_LOG_PROTOCOLS.md)

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

### Hardware Integration (Week 10)
| # | Folder | Topic |
|---|--------|-------|
| 14 | [`14_stm32_can_bxcan`](examples/14_stm32_can_bxcan/) | bxCAN ISR → J1939 decode task, ties FreeRTOS to `automotive_protocols/` |

---

## Automotive Protocols Track

| # | Folder | Focus |
|---|--------|-------|
| 01 | [`topic_01_serial_comm_basics`](automotive_protocols/topic_01_serial_comm_basics/) | UART/SPI/I2C for ECU/diagnostic-connector links |
| 02 | [`topic_02_can_bus`](automotive_protocols/topic_02_can_bus/) | CAN 2.0A/B framing, arbitration, bit timing, error states |
| 03 | [`topic_03_j1939_transport`](automotive_protocols/topic_03_j1939_transport/) | J1939 PGN/SPN, 29-bit ID, BAM/RTS-CTS transport |
| 04 | [`topic_04_iso_tp`](automotive_protocols/topic_04_iso_tp/) | ISO 15765-2 segmentation/reassembly, flow control |
| 05 | [`topic_05_uds`](automotive_protocols/topic_05_uds/) | UDS session control, security access, DTCs |
| 06 | [`topic_06_uds_bootloader_flashing`](automotive_protocols/topic_06_uds_bootloader_flashing/) | Full ECU reflash sequence |
| 07 | [`topic_07_lin_flexray_ethernet`](automotive_protocols/topic_07_lin_flexray_ethernet/) | LIN, FlexRay, Automotive Ethernet survey |

Details: [`automotive_protocols/README.md`](automotive_protocols/README.md)

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

**Not sure where to start? Open [`MASTER_STUDY_PLAN.md`](MASTER_STUDY_PLAN.md)** — it tells you exactly which week/folder to be in based on what you've already completed.

**Today (if starting cold):** `c_practice/topic_01_types_variables`, then `dsa_practice/topic_01_arrays` (weeks 1–4), before touching FreeRTOS.

**If C/DSA done:** Open [`PRACTICE_GUIDE.md`](PRACTICE_GUIDE.md) Day 1, or [`ADVANCED_PRACTICE_GUIDE.md`](ADVANCED_PRACTICE_GUIDE.md) Day 11 if FreeRTOS basics are done.

**If FreeRTOS done:** Start `automotive_protocols/topic_01_serial_comm_basics` (week 7).

**End goal:** Complete [`projects/Advanced_FreeRTOS_Lab/README.md`](projects/Advanced_FreeRTOS_Lab/README.md) capstone and [`examples/14_stm32_can_bxcan`](examples/14_stm32_can_bxcan/) hardware integration.

**Interview goal:** Work through both [`FREERTOS_INTERVIEW_PREP.md`](FREERTOS_INTERVIEW_PREP.md) and [`AUTOMOTIVE_INTERVIEW_PREP.md`](AUTOMOTIVE_INTERVIEW_PREP.md) and explain every choice without notes — see the "Definition of ready to interview" checklist in [`MASTER_STUDY_PLAN.md`](MASTER_STUDY_PLAN.md).
