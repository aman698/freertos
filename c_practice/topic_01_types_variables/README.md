# Topic 01 — Types & Variables

Fixed-width types from `<stdint.h>` are the foundation of embedded C. Hardware registers, ADC readings, and protocol bytes have explicit bit widths — plain `int` size varies by compiler and platform.

## Brief Theory

| Type | Bits | Typical use |
|------|------|-------------|
| `uint8_t` | 8 | GPIO port byte, UART data, small counters |
| `uint16_t` | 16 | ADC result, timer period (16-bit regs) |
| `uint32_t` | 32 | Addresses, 32-bit MMIO, millisecond ticks |
| `int32_t` | 32 signed | Sensor delta, signed measurements |

- **`sizeof(type)`** returns size in **bytes**, not bits.
- **Signed vs unsigned:** mixing them in comparisons can surprise you (`-1 < 0u` is false).
- **Overflow:** unsigned wrap is defined (`255 + 1 → 0` for `uint8_t`); signed overflow is undefined in C.
- **`char` vs `uint8_t`:** `char` may be signed; use `uint8_t` for raw binary data (sensor frames, flash bytes).
- **Limits:** `UINT8_MAX`, `INT16_MIN`, etc. from `<stdint.h>`; also `<limits.h>` for `CHAR_BIT`.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_stdint_sizes.c](solutions/ex01_stdint_sizes.c) | Print `sizeof` for core fixed-width types | Lines showing 1, 2, 4 byte sizes | `sizeof`, fixed-width types |
| 02 | [ex02_uint8_max.c](solutions/ex02_uint8_max.c) | Show `UINT8_MAX` and increment wrap | `255` then `0` after wrap | Unsigned overflow wrap |
| 03 | [ex03_signed_unsigned.c](solutions/ex03_signed_unsigned.c) | Compare `int8_t -1` with `uint8_t 255` | Explains equality / comparison trap | Signed vs unsigned |
| 04 | [ex04_char_vs_uint8.c](solutions/ex04_char_vs_uint8.c) | Store sensor byte `0xFF` in `char` vs `uint8_t` | Different printed values if char is signed | `char` signedness |
| 05 | [ex05_int16_sensor.c](solutions/ex05_int16_sensor.c) | Convert raw ADC to signed temperature | `-12 C` from two's complement raw | `int16_t` for signed data |
| 06 | [ex06_uint32_counter.c](solutions/ex06_uint32_counter.c) | Simulate 32-bit free-running tick counter | Large tick value printed | `uint32_t` range |
| 07 | [ex07_overflow_demo.c](solutions/ex07_overflow_demo.c) | Add two `uint8_t` values that exceed 255 | Wrapped result `44` (200+100) | Arithmetic overflow |
| 08 | [ex08_limits_constants.c](solutions/ex08_limits_constants.c) | Print min/max from stdint limits | INT16_MIN, UINT32_MAX, etc. | Limit macros |
| 09 | [ex09_gpio_shadow_init.c](solutions/ex09_gpio_shadow_init.c) | Initialize GPIO shadow register variables | `ODR=0x0000`, pins configured | Variable initialization |
| 10 | [ex10_sizeof_pitfall.c](solutions/ex10_sizeof_pitfall.c) | Compare `sizeof(uint32_t)` vs `sizeof(uint32_t*)` | 4 vs 8 (on 64-bit PC) | `sizeof` expression |
| 11 | [ex11_stdbool_flags.c](solutions/ex11_stdbool_flags.c) | Use `bool` for alarm and ready flags | `alarm=true ready=false` | `<stdbool.h>` |
| 12 | [ex12_adc_scaling.c](solutions/ex12_adc_scaling.c) | Scale 12-bit ADC `uint16_t` to millivolts | `3300 mV` at full scale | Type choice for ADC |

---

## Build & Run

```bash
cd c_practice/topic_01_types_variables/solutions
gcc ex01_stdint_sizes.c -o ex01 && ./ex01
```
