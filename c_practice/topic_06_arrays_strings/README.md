# Topic 06 — Arrays & Strings

**Level:** Intermediate · **Exercises:** 12 · **Context:** STM32 buffers, UART lines, sensor formatting

---

## Brief Theory

### Arrays

- Fixed-size contiguous memory: `uint8_t samples[8];`
- Index `0 .. N-1`; no runtime bounds check in C
- Name **decays** to pointer to first element when passed to functions
- 2D arrays are **row-major**: `matrix[row][col]` → `row * COLS + col`

### Strings

- C strings are `char` arrays ending with `'\0'`
- `strlen(s)` counts characters **excluding** the terminator
- Never assume `strcpy` is safe — always track destination size
- Prefer `snprintf(buf, sizeof(buf), ...)` for formatted output

### Embedded Patterns

```c
char line[64];
int n = snprintf(line, sizeof(line), "T=%d\r\n", temp_c);
/* n = chars that would be written (excl. '\0'); truncate if n >= sizeof(buf) */

uint8_t hex = (uint8_t)((line[0] >= 'A' ? line[0]-'A'+10 : line[0]-'0') << 4) | ...;
```

- UART RX: accumulate bytes into a line buffer until `\r` or `\n`
- Parse tokens with manual loops or small state machines (no `malloc` required)

---

## Exercises

| # | File | Problem |
|---|------|---------|
| 01 | `ex01_array_basics.c` | Initialize and sum a `uint8_t` ADC sample buffer |
| 02 | `ex02_array_decay.c` | Pass array to function; show decay vs `sizeof` in caller |
| 03 | `ex03_2d_array.c` | 2D LED matrix lookup: turn on pixel (row, col) |
| 04 | `ex04_string_literal.c` | Compare string literal vs `char[]` mutability |
| 05 | `ex05_strlen.c` | Implement `my_strlen` and compare with library |
| 06 | `ex06_safe_strcpy.c` | Bounded copy helper (STM32-safe string copy) |
| 07 | `ex07_snprintf_sensor.c` | Format temperature/humidity line with `snprintf` |
| 08 | `ex08_parse_csv.c` | Parse `"12,34,56"` into three integers |
| 09 | `ex09_hex_string_to_bytes.c` | Convert `"A5F0"` ASCII hex to two bytes |
| 10 | `ex10_uart_line_buffer.c` | Simulate UART RX into line buffer until newline |
| 11 | `ex11_command_compare.c` | Match incoming command against `"LED ON"` / `"LED OFF"` |
| 12 | `ex12_at_command_parser.c` | Mini parser for `AT+TEMP?` style commands |

---

## Build

```bash
cd solutions
gcc ex01_array_basics.c -o ex01 && ./ex01
```
