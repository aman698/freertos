# Topic 08 — Bit Manipulation

Every GPIO, timer, and peripheral register is manipulated with bit masks. Master set/clear/toggle/test macros before reading STM32 reference manuals.

## Brief Theory

| Operation | Expression | Example |
|-----------|------------|---------|
| Set bit n | `reg \|= (1U << n)` | Turn LED on |
| Clear bit n | `reg &= ~(1U << n)` | Turn LED off |
| Toggle bit n | `reg ^= (1U << n)` | Flip pin state |
| Test bit n | `(reg >> n) & 1U` | Read pin input |
| Extract field | `(reg >> pos) & mask` | Get prescaler |
| Insert field | clear then OR | Write multi-bit field |

**BIT(n) macro:** `#define BIT(n) (1UL << (n))` — use `UL` for 32-bit registers.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_bit_macro.c](solutions/ex01_bit_macro.c) | Define and use BIT(n) macro | Mask values printed | BIT macro |
| 02 | [ex02_set_bit.c](solutions/ex02_set_bit.c) | Set single bit in shadow ODR | Bit 5 set | Set bit |
| 03 | [ex03_clear_bit.c](solutions/ex03_clear_bit.c) | Clear single bit | Bit cleared | Clear bit |
| 04 | [ex04_toggle_bit.c](solutions/ex04_toggle_bit.c) | Toggle LED bit twice | 0→1→0 | Toggle |
| 05 | [ex05_test_bit.c](solutions/ex05_test_bit.c) | Test if input bit is high | Pin state string | Test bit |
| 06 | [ex06_field_extract.c](solutions/ex06_field_extract.c) | Extract 4-bit field | Field value shown | Extract |
| 07 | [ex07_field_insert.c](solutions/ex07_field_insert.c) | Insert value into field | Register updated | Insert |
| 08 | [ex08_parity.c](solutions/ex08_parity.c) | Compute even parity bit | Parity for byte | Parity |
| 09 | [ex09_popcount.c](solutions/ex09_popcount.c) | Count set bits in word | Population count | popcount |
| 10 | [ex10_gpio_shadow.c](solutions/ex10_gpio_shadow.c) | Shadow register set/clear | ODR shadow ops | GPIO shadow |
| 11 | [ex11_multibit_field.c](solutions/ex11_multibit_field.c) | Read/write 3-bit mode field | Mode changed | Multi-bit field |
| 12 | [ex12_register_bits.c](solutions/ex12_register_bits.c) | Full CR register setup | Multiple bits set | Combined ops |

---

## Build & Run

```bash
cd c_practice/topic_08_bit_manipulation/solutions
gcc ex01_bit_macro.c -o ex01 && ./ex01
```
