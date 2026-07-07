# Topic 04 — Functions & Scope

Functions modularize firmware. Understanding scope, `static`, pass-by-value vs pointer, and recursion is essential for drivers and HAL-style code.

## Brief Theory

| Concept | Meaning | Embedded use |
|---------|---------|--------------|
| Function | Named reusable block | `gpio_write()`, `adc_read()` |
| Scope | Where name is visible | Block, file, global |
| `static` (local) | Persists between calls | Debounce counter, ring index |
| `static` (global) | File-private linkage | Driver internal state |
| Pass by value | Copy of argument | Small integers, flags |
| Pass by pointer | Address — can modify caller data | Buffers, out-parameters |
| Recursion | Function calls itself | Tree walk (rare on MCU; watch stack) |

**Tips:** Use pointers for output parameters and large structs. Keep recursion shallow or avoid on small stacks. Declare prototypes in headers for multi-file projects.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_basic_function.c](solutions/ex01_basic_function.c) | Write `celsius_to_fahrenheit()` | Converted values printed | Basic function |
| 02 | [ex02_pass_by_value.c](solutions/ex02_pass_by_value.c) | Increment copy — caller unchanged | Original stays same | Pass by value |
| 03 | [ex03_pass_by_pointer.c](solutions/ex03_pass_by_pointer.c) | Increment via pointer | Caller variable updated | Pass by pointer |
| 04 | [ex04_static_local.c](solutions/ex04_static_local.c) | `static` local call counter | Count persists across calls | Static local |
| 05 | [ex05_static_file_scope.c](solutions/ex05_static_file_scope.c) | File-static helper pattern | Internal API only | Static linkage |
| 06 | [ex06_prototype_forward.c](solutions/ex06_prototype_forward.c) | Forward declaration before use | Functions call each other | Prototypes |
| 07 | [ex07_recursion_factorial.c](solutions/ex07_recursion_factorial.c) | Recursive factorial | `5! = 120` | Recursion |
| 08 | [ex08_recursion_fibonacci.c](solutions/ex08_recursion_fibonacci.c) | Recursive Fibonacci | Sequence 0..6 | Recursion depth |
| 09 | [ex09_swap_pointers.c](solutions/ex09_swap_pointers.c) | Swap two integers via pointers | Values exchanged | Pointer params |
| 10 | [ex10_scope_shadow.c](solutions/ex10_scope_shadow.c) | Inner block shadows outer name | Different scopes shown | Block scope |
| 11 | [ex11_inline_helper.c](solutions/ex11_inline_helper.c) | `static inline` bit helper | Inlined-style mask op | Inline helper |
| 12 | [ex12_modular_driver.c](solutions/ex12_modular_driver.c) | Mini driver: init/read/deinit | Full driver flow | Modular functions |

---

## Build & Run

```bash
cd c_practice/topic_04_functions_scope/solutions
gcc ex01_basic_function.c -o ex01 && ./ex01
```
