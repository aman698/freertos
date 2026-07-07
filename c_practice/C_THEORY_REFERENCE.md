# Embedded C Theory Reference — Complete Concept Guide

Quick theory for all 15 practice topics. Pair with topic README + solve exercises.

---

## 1. Types & Variables (`stdint.h`)

Embedded firmware avoids plain `int` ambiguity. Use fixed-width types:

| Type | Typical size | Use |
|------|--------------|-----|
| `uint8_t` | 8 bit | Bytes, GPIO ports |
| `uint16_t` | 16 bit | Half-word, ADC |
| `uint32_t` | 32 bit | Addresses, counters |
| `int32_t` | 32 bit signed | Sensor delta |

`sizeof(type)` returns bytes. `UINT8_MAX`, `UINT32_MAX` from `<stdint.h>` / `<limits.h>`.

**Rule:** Match hardware register width (STM32 GPIO: 16-bit IDR, 32-bit moder).

---

## 2. Operators

| Class | Examples | Embedded note |
|-------|----------|---------------|
| Arithmetic | `+ - * / %` | Watch overflow on `uint8_t` |
| Relational | `== != < >` | Never `float == float` |
| Logical | `&& \|\| !` | Short-circuit saves CPU |
| Bitwise | `& \| ^ ~ << >>` | Register programming |
| Assignment | `= += &= \|=` | `x \|= MASK` sets bits |

**Precedence:** `()` > `! ~` > `* / %` > `+ -` > `<< >>` > `< >` > `==` > `&` > `^` > `|` > `&&` > `||` > `?:` > `=`

---

## 3. Control Flow

- `if / else if / else` — default path for safety
- `switch` — dispatch on enum/state; use `default`
- `for` — known iteration count
- `while` — wait-until-condition (watchdog risk in production)
- `do-while` — at least once
- `break / continue` — loop control

**Embedded:** Avoid infinite `while(1)` without WDT or RTOS block in production tasks.

---

## 4. Functions & Scope

```c
static void helper(void);  /* file scope only */
void public_api(void);     /* extern linkage */
```

- **Stack frame:** locals die when function returns
- **static local:** retains value between calls
- **Pass by value:** copy; use pointer for large structs
- **Return:** never return pointer to local stack variable

---

## 5. Pointers

```c
uint32_t x = 10;
uint32_t *p = &x;   /* p holds address of x */
*p = 20;            /* dereference: write through pointer */
```

- `NULL` — invalid / not initialized
- `void *` — generic; cast before use
- Pointer arithmetic: `p + 1` moves by `sizeof(*p)` bytes

---

## 6. Arrays & Strings

```c
uint8_t buf[16];
char msg[] = "OK\r\n";  /* includes '\0' */
```

- Array name decays to pointer to first element
- `strlen` does not include `'\0'`
- No bounds checking — you enforce length
- `snprintf(buf, sizeof(buf), fmt, ...)` — safe formatting

---

## 7. Structures & Unions

```c
typedef struct {
    uint32_t baud;
    uint8_t  data_bits;
} UartConfig_t;
```

- Members laid out in order; compiler may **pad** for alignment
- `union` — all members share same memory (one active)
- `typedef struct { ... } Name_t` — common embedded style

---

## 8. Bit Manipulation

```c
#define BIT(n)  (1U << (n))
reg |= BIT(5);           /* set bit 5 */
reg &= ~BIT(5);          /* clear */
reg ^= BIT(5);          /* toggle */
if (reg & BIT(5)) { }   /* test */
```

Extract field: `(reg >> pos) & mask`. Merge: `(reg & ~mask) | (val << pos)`.

---

## 9. const & volatile

| Qualifier | Meaning |
|-----------|---------|
| `const` | Read-only; may live in flash |
| `volatile` | Compiler must re-read every access (hardware, ISR-shared) |
| `const volatile` | MMIO read-only registers |

```c
volatile uint32_t * const GPIOA_ODR = (uint32_t *)0x40020014UL;
```

**Never** optimize away reads of hardware with plain `uint32_t *`.

---

## 10. Preprocessor

```c
#define LED_PIN  5
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#if defined(STM32F411xx)
  ...
#endif
```

- `#include` — text inclusion
- `#define` — macro replace (watch parentheses)
- `#if / #ifdef` — conditional compile
- `static inline` often replaces risky macros in modern code

---

## 11. Memory Model

| Region | Lifetime | Typical use |
|--------|----------|-------------|
| Stack | Function call | Locals, small buffers |
| Static / global | Program lifetime | Config tables, handles |
| Heap | `malloc` until `free` | Queues, dynamic (avoid in ISR) |
| Flash (.rodata) | `const` constants | Lookup tables |

Stack overflow = silent corruption. Measure worst-case depth.

---

## 12. Function Pointers

```c
typedef void (*Callback_t)(void);
Callback_t cb = &MyHandler;
cb();
```

Dispatch table, HAL weak callbacks, state machine actions. Ensure pointer valid before call.

---

## 13. MMIO Registers

Memory-mapped I/O: peripheral at fixed address.

```c
#define GPIOA_MODER  (*(volatile uint32_t *)0x40020000UL)
GPIOA_MODER |= (1U << 10);  /* often use struct overlay instead */
```

Read-modify-write race with ISRs — use atomic bit ops or disable interrupt briefly.

---

## 14. Data Structures

- **Singly linked list:** `struct Node { data; struct Node *next; }`
- **Ring buffer:** head/tail indices, power-of-2 size for fast modulo
- **FIFO queue:** embedded in FreeRTOS `xQueue`

---

## 15. State Machines

```c
typedef enum { ST_IDLE, ST_DEBOUNCE, ST_PRESSED } BtnState_t;
```

Transition table: `(state, event) → next_state, action`. Cleaner than nested `if` for protocols, UI, debounce.

---

**Practice:** [`README.md`](README.md) · **Schedule:** [`C_PRACTICE_GUIDE.md`](C_PRACTICE_GUIDE.md)
