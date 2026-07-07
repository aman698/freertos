# Topic 12 - Function Pointers

Function pointers store the address of callable code. In embedded C they are used for callbacks, driver hooks, interrupt tables, command dispatch, and state-machine actions.

## Brief Theory

| Pattern | Example | Embedded use |
|---------|---------|--------------|
| Basic pointer | `void (*fn)(void)` | Deferred action |
| Typedef | `typedef void (*Cb_t)(void)` | Cleaner APIs |
| Callback parameter | `register_cb(handler)` | HAL/user hooks |
| Dispatch table | `table[id]()` | Command or IRQ routing |
| Function pointer in struct | `.handler = fn` | Driver objects |

**Tips:** Check pointers before calling. Use typedefs for readability. Keep callback execution short if it may run from ISR context.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_basic_function_pointer.c](solutions/ex01_basic_function_pointer.c) | Store and call function | Handler called | Function pointer |
| 02 | [ex02_typedef_callback.c](solutions/ex02_typedef_callback.c) | Use callback typedef | Callback invoked | typedef |
| 03 | [ex03_callback_parameter.c](solutions/ex03_callback_parameter.c) | Pass callback to function | Event reported | Callback arg |
| 04 | [ex04_dispatch_table.c](solutions/ex04_dispatch_table.c) | Command dispatch table | Commands execute | Table of funcs |
| 05 | [ex05_math_operations.c](solutions/ex05_math_operations.c) | Select arithmetic op | Result printed | Strategy |
| 06 | [ex06_struct_with_handler.c](solutions/ex06_struct_with_handler.c) | Handler inside struct | Driver handler runs | Function member |
| 07 | [ex07_null_callback_check.c](solutions/ex07_null_callback_check.c) | Guard callback call | Safe missing callback | NULL check |
| 08 | [ex08_sort_comparator.c](solutions/ex08_sort_comparator.c) | Comparator callback | Sorted array | Comparator |
| 09 | [ex09_isr_vector_sim.c](solutions/ex09_isr_vector_sim.c) | Simulated vector table | IRQ handlers called | ISR table |
| 10 | [ex10_timer_callback.c](solutions/ex10_timer_callback.c) | Timer expiry callback | Timer event printed | Timer hook |
| 11 | [ex11_command_parser.c](solutions/ex11_command_parser.c) | Map text command to handler | LED commands | Command table |
| 12 | [ex12_state_action_table.c](solutions/ex12_state_action_table.c) | State action table | State actions run | FSM actions |

---

## Build & Run

```bash
cd c_practice/topic_12_function_pointers/solutions
gcc ex01_basic_function_pointer.c -o ex01 && ./ex01
```
