# Topic 09 — const & volatile

`volatile` tells the compiler hardware or ISRs may change a variable at any time. `const` marks read-only data. Together they model MMIO registers and flash-resident lookup tables.

## Brief Theory

| Qualifier | Meaning | Embedded use |
|-----------|---------|--------------|
| `const` | Must not be modified | Flash lookup tables, config |
| `volatile` | May change unexpectedly | MMIO, ISR flags, tick counter |
| `const volatile` | Readable HW register | Status register (read-only HW) |
| `volatile *` | Pointer to MMIO | `#define REG (*(volatile uint32_t*)addr)` |

**Tips:** Never use `volatile` to fix race conditions between tasks — use mutex/atomic. Always declare ISR-shared flags as `volatile`. MMIO pointers must be `volatile`.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_const_variable.c](solutions/ex01_const_variable.c) | const config values | Values printed, immutable | const data |
| 02 | [ex02_const_pointer.c](solutions/ex02_const_pointer.c) | const pointer to data | Read-only via pointer | const T* |
| 03 | [ex03_volatile_counter.c](solutions/ex03_volatile_counter.c) | volatile tick counter | ISR-style increment | volatile var |
| 04 | [ex04_volatile_mmio.c](solutions/ex04_volatile_mmio.c) | Simulated MMIO read/write | Register access | volatile MMIO |
| 05 | [ex05_const_volatile.c](solutions/ex05_const_volatile.c) | const volatile status reg | Read-only HW reg | const volatile |
| 06 | [ex06_isr_shared_flag.c](solutions/ex06_isr_shared_flag.c) | ISR sets flag, main clears | Flag handshake | ISR flag |
| 07 | [ex07_read_only_table.c](solutions/ex07_read_only_table.c) | const lookup in flash | LUT lookup result | const table |
| 08 | [ex08_mmio_pointer_cast.c](solutions/ex08_mmio_pointer_cast.c) | Cast address to volatile ptr | Typed register access | MMIO cast |
| 09 | [ex09_optimization_trap.c](solutions/ex09_optimization_trap.c) | Why volatile matters | With/without volatile | Optimization |
| 10 | [ex10_volatile_struct.c](solutions/ex10_volatile_struct.c) | volatile struct overlay | Struct MMIO | volatile struct |
| 11 | [ex11_const_parameter.c](solutions/ex11_const_parameter.c) | const input buffer param | Function reads only | const param |
| 12 | [ex12_embedded_flags.c](solutions/ex12_embedded_flags.c) | Multiple volatile flags | Event flags demo | Flag set |

---

## Build & Run

```bash
cd c_practice/topic_09_const_volatile/solutions
gcc ex01_const_variable.c -o ex01 && ./ex01
```
