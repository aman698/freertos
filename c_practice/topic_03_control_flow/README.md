# Topic 03 — Control Flow

`if`, `switch`, loops, `break`, `continue`, and `goto` drive every firmware decision loop — threshold checks, mode selection, polling, and error cleanup.

## Brief Theory

| Construct | Use in embedded |
|-----------|-----------------|
| `if / else` | ADC thresholds, fault detection |
| `switch` | LED modes, protocol states, command dispatch |
| `for` | Buffer scan, sample averaging |
| `while` | UART ready-bit polling, wait-for-flag |
| `do-while` | At-least-once menu / retry loops |
| `break` | Exit search loop when match found |
| `continue` | Skip invalid sensor samples |
| `goto` | Single exit error cleanup (driver init) |

**Tips:** Prefer `switch` over long `if-else` chains for discrete modes. Avoid deep nesting — early `return` or `goto cleanup` keeps init code readable. Never fall through `switch` cases unless intentional (comment it).

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_if_threshold.c](solutions/ex01_if_threshold.c) | Compare ADC value to high threshold | `ALARM: over limit` | `if` |
| 02 | [ex02_if_else_chain.c](solutions/ex02_if_else_chain.c) | Classify temperature into LOW/OK/HIGH | Three zone labels | `if-else` chain |
| 03 | [ex03_switch_led_mode.c](solutions/ex03_switch_led_mode.c) | Select blink pattern via mode enum | Mode 0/1/2 behavior | `switch` |
| 04 | [ex04_for_sum.c](solutions/ex04_for_sum.c) | Sum 8 ADC samples with `for` | Sum and average printed | `for` loop |
| 05 | [ex05_while_poll.c](solutions/ex05_while_poll.c) | Poll status flag until ready | `Ready after N polls` | `while` |
| 06 | [ex06_do_while_retry.c](solutions/ex06_do_while_retry.c) | Retry SPI transfer up to 3 times | Attempt count shown | `do-while` |
| 07 | [ex07_break_search.c](solutions/ex07_break_search.c) | Find first sample above limit | Index of match | `break` |
| 08 | [ex08_continue_filter.c](solutions/ex08_continue_filter.c) | Skip out-of-range readings | Valid average only | `continue` |
| 09 | [ex09_nested_loops.c](solutions/ex09_nested_loops.c) | Scan 4×4 key matrix | Row/col of pressed key | Nested loops |
| 10 | [ex10_switch_no_fallthrough.c](solutions/ex10_switch_no_fallthrough.c) | Handle UART command chars | Distinct per-case action | `switch` cases |
| 11 | [ex11_goto_cleanup.c](solutions/ex11_goto_cleanup.c) | Init steps with error goto | Cleanup on failure | `goto` cleanup |
| 12 | [ex12_control_combined.c](solutions/ex12_control_combined.c) | Combined flow: poll, filter, act | Full sensor pipeline | Mixed control flow |

---

## Build & Run

```bash
cd c_practice/topic_03_control_flow/solutions
gcc ex01_if_threshold.c -o ex01 && ./ex01
```
