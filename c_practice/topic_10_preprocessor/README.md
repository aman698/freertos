# Topic 10 — Preprocessor

The C preprocessor runs before compilation: `#define`, `#include`, `#if`, and token tricks build configurable, portable firmware.

## Brief Theory

| Directive | Purpose | Embedded use |
|-----------|---------|--------------|
| `#define` | Text substitution | Pin numbers, clock Hz |
| Macro function | `#define MAX(a,b)` | Min/max, bit ops (parens!) |
| `#include` | Pull in headers | HAL, board config |
| `#if / #ifdef` | Conditional compile | Feature flags, chip select |
| Include guards | `#ifndef HDR_H` | Prevent double include |
| `#` stringify | `"#x"` → `"x"` | Debug print macro |
| `##` paste | `a##b` → `ab` | Token concatenation |

**Tips:** Parenthesize macro arguments. Prefer `static inline` over complex macros when debugging. Never `#define` semicolon-heavy multi-statement macros without `do { } while(0)`.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_define_constant.c](solutions/ex01_define_constant.c) | #define pin and clock | Constants used | #define |
| 02 | [ex02_function_macro.c](solutions/ex02_function_macro.c) | MIN/MAX macro | Min/max values | Function-like macro |
| 03 | [ex03_if_def.c](solutions/ex03_if_def.c) | #ifdef feature flag | Conditional code path | #ifdef |
| 04 | [ex04_include_guard.c](solutions/ex04_include_guard.c) | Include guard demo | Safe double include | Include guard |
| 05 | [ex05_stringify.c](solutions/ex05_stringify.c) | # operator stringify | Variable name as string | Stringify |
| 06 | [ex06_token_paste.c](solutions/ex06_token_paste.c) | ## token paste | Generated symbol names | Token paste |
| 07 | [ex07_conditional_compile.c](solutions/ex07_conditional_compile.c) | #if chip selection | Selected chip config | #if |
| 08 | [ex08_macro_pitfalls.c](solutions/ex08_macro_pitfalls.c) | Macro side effects demo | Safe vs unsafe macro | Pitfalls |
| 09 | [ex09_array_size_macro.c](solutions/ex09_array_size_macro.c) | ARRAY_SIZE macro | Element count | ARRAY_SIZE |
| 10 | [ex10_feature_flags.c](solutions/ex10_feature_flags.c) | Compile-time features | Enabled features list | Feature flags |
| 11 | [ex11_bit_macro_header.c](solutions/ex11_bit_macro_header.c) | BIT/SET/CLEAR macros | Register ops via macro | Bit macros |
| 12 | [ex12_board_config.c](solutions/ex12_board_config.c) | Board config header style | NUCLEO config printed | Config pattern |

---

## Build & Run

```bash
cd c_practice/topic_10_preprocessor/solutions
gcc ex01_define_constant.c -o ex01 && ./ex01
gcc ex04_include_guard.c -o ex04 -I.
```
