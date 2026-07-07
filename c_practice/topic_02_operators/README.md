# Topic 02 — Operators

Arithmetic, relational, logical, and bitwise operators appear in every embedded driver. Precedence mistakes in register expressions are a common source of bugs.

## Brief Theory

| Class | Operators | Embedded use |
|-------|-----------|--------------|
| Arithmetic | `+ - * / %` | Scaling ADC; `%` for circular buffer index |
| Relational | `== != < > <= >=` | Threshold checks, range validation |
| Logical | `&& \|\| !` | Short-circuit: second operand skipped if result known |
| Bitwise | `& \| ^ ~ << >>` | GPIO masks, set/clear/toggle bits |
| Assignment | `= += -= &= \|=` | `reg \|= PIN_MASK` to set pin |

**Precedence (high → low):** `()` → unary `! ~` → `* / %` → `+ -` → `<< >>` → comparisons → `&` → `^` → `|` → `&&` → `||` → `?:` → `=`

**Tip:** When in doubt, add parentheses. Firmware readability beats cleverness.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_basic_arithmetic.c](solutions/ex01_basic_arithmetic.c) | Compute period from prescaler and ARR | Timer period printed in counts | `+ - * /` |
| 02 | [ex02_modulo_wrap.c](solutions/ex02_modulo_wrap.c) | Circular buffer index with `%` | Index wraps 0..7 | Modulo |
| 03 | [ex03_precedence.c](solutions/ex03_precedence.c) | Evaluate expression with and without parens | Two different results shown | Precedence |
| 04 | [ex04_logical_short.c](solutions/ex04_logical_short.c) | Demonstrate `&&` and `\|\|` short-circuit | Second call skipped | Logical operators |
| 05 | [ex05_bitwise_and_mask.c](solutions/ex05_bitwise_and_mask.c) | Read GPIO pin state with `&` mask | Pin high/low detected | Bitwise AND |
| 06 | [ex06_bitwise_or_set.c](solutions/ex06_bitwise_or_set.c) | Set LED bit with `\|` | ODR bit set | Bitwise OR |
| 07 | [ex07_shift_left.c](solutions/ex07_shift_left.c) | Create pin mask with `<<` | `0x0020` for bit 5 | Left shift |
| 08 | [ex08_shift_right.c](solutions/ex08_shift_right.c) | Extract nibble with `>>` and `&` | Upper/lower nibble | Right shift |
| 09 | [ex09_compound_assign.c](solutions/ex09_compound_assign.c) | Use `&=`, `\|=`, `^=` on shadow reg | Toggle and clear bits | Compound assign |
| 10 | [ex10_relational.c](solutions/ex10_relational.c) | Compare ADC value to thresholds | LOW / OK / HIGH zone | Relational ops |
| 11 | [ex11_unary_not.c](solutions/ex11_unary_not.c) | Use `!` and `~` on flags and masks | Inverted logic shown | Unary operators |
| 12 | [ex12_embedded_expr.c](solutions/ex12_embedded_expr.c) | Combined mask/shift/compare expression | Full register decode | Mixed expression |

---

## Build & Run

```bash
cd c_practice/topic_02_operators/solutions
gcc ex01_basic_arithmetic.c -o ex01 && ./ex01
```
