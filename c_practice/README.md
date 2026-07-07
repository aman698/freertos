# Embedded C Practice — Basic to Advanced (STM32 Context)

**180 hands-on programs** · **15 topics** · **12 exercises per topic** · Full source + brief theory

Runs on **PC (GCC)** for fast iteration, then maps to **STM32CubeIDE** / NUCLEO-F411RE.

---

## Learning Path

| Phase | Topics | Level | Exercises |
|-------|--------|-------|-----------|
| **1 — Foundations** | 01–04 | Basic | 48 |
| **2 — Memory & Data** | 05–08 | Intermediate | 48 |
| **3 — Embedded Core** | 09–12 | Embedded | 48 |
| **4 — Advanced** | 13–15 | Advanced | 36 |

**Total: 180 programs**

---

## How to Practice

### On PC (recommended first)

```bash
cd c_practice
gcc topic_01_types_variables/solutions/ex01_stdint_sizes.c -o ex01 && ./ex01
```

Or build all in a topic:

```bash
cd topic_05_pointers/solutions
for f in ex*.c; do gcc "$f" -o "${f%.c}" && ./"${f%.c}"; done
```

### On STM32 (optional)

Copy exercise logic into `Core/Src/main.c` USER CODE, print via USART2 (`printf` retarget from Example 03).

### Daily workflow

1. Read topic **README.md** (theory + problem list)
2. Solve **without** looking at `solutions/` (30–60 min)
3. Compare with solution `.c`
4. Log in [`PRACTICE_LOG_C.md`](PRACTICE_LOG_C.md)

---

## All Topics

| # | Folder | Focus |
|---|--------|-------|
| 01 | [`topic_01_types_variables`](topic_01_types_variables/) | `stdint.h`, sizes, signed/unsigned |
| 02 | [`topic_02_operators`](topic_02_operators/) | Arithmetic, logic, precedence |
| 03 | [`topic_03_control_flow`](topic_03_control_flow/) | if, switch, for, while |
| 04 | [`topic_04_functions_scope`](topic_04_functions_scope/) | Functions, static, scope |
| 05 | [`topic_05_pointers`](topic_05_pointers/) | Addresses, `*`, `&`, NULL |
| 06 | [`topic_06_arrays_strings`](topic_06_arrays_strings/) | Buffers, `strlen`, parsing |
| 07 | [`topic_07_structs_unions`](topic_07_structs_unions/) | Struct layout, unions |
| 08 | [`topic_08_bit_manipulation`](topic_08_bit_manipulation/) | Masks, shifts, GPIO style |
| 09 | [`topic_09_const_volatile`](topic_09_const_volatile/) | `volatile` MMIO, `const` |
| 10 | [`topic_10_preprocessor`](topic_10_preprocessor/) | Macros, `#if`, headers |
| 11 | [`topic_11_memory`](topic_11_memory/) | Stack, heap, static, overflow |
| 12 | [`topic_12_function_pointers`](topic_12_function_pointers/) | Callbacks, dispatch tables |
| 13 | [`topic_13_mmio_registers`](topic_13_mmio_registers/) | Register maps, read-modify-write |
| 14 | [`topic_14_data_structures`](topic_14_data_structures/) | Linked list, ring buffer |
| 15 | [`topic_15_state_machines`](topic_15_state_machines/) | FSM, debounce, parser |

---

## Guides

| Doc | Purpose |
|-----|---------|
| [`C_PRACTICE_GUIDE.md`](C_PRACTICE_GUIDE.md) | Day-by-day schedule, verify checklists |
| [`C_THEORY_REFERENCE.md`](C_THEORY_REFERENCE.md) | All concepts in one reference |
| [`PRACTICE_LOG_C.md`](PRACTICE_LOG_C.md) | Daily log template |

---

## Link to FreeRTOS Track

| C topic | FreeRTOS example |
|---------|------------------|
| 08 Bit manipulation | GPIO, EXTI |
| 09 volatile / MMIO | UART, timer registers |
| 11 Memory / stack | Example 06 stack monitor |
| 14 Ring buffer | Example 10 stream buffer |
| 15 State machines | Example 02 debounce |
| 12 Function pointers | HAL callbacks, timer CB |

**RTOS path:** [`../PRACTICE_GUIDE.md`](../PRACTICE_GUIDE.md)  
**Debugger path:** [`../docs/DEBUGGING_GUIDE.md`](../docs/DEBUGGING_GUIDE.md)

---

## Start Here

Open [`topic_01_types_variables/README.md`](topic_01_types_variables/README.md) → solve `ex01` → work through topic 01 → topic 15.
