# Topic 11 - Memory Model

C programs use different memory areas: stack for function locals, static storage for globals/static locals, heap for dynamic allocation, and read-only memory for `const` data.

## Brief Theory

| Area | Lifetime | Embedded use | Risk |
|------|----------|--------------|------|
| Stack | Function call | Small locals, return addresses | Overflow corrupts memory |
| Static/global | Whole program | Driver state, handles, flags | Hidden shared state |
| Heap | `malloc` to `free` | Variable-size buffers | Fragmentation/leaks |
| Read-only data | Whole program | Lookup tables, strings | Must not be modified |

**Tips:** Avoid large stack arrays in RTOS tasks. Prefer static buffers for fixed firmware resources. If you use heap, check `malloc` and define ownership clearly.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_stack_local.c](solutions/ex01_stack_local.c) | Show local variable lifetime | Counter resets | Stack local |
| 02 | [ex02_static_local.c](solutions/ex02_static_local.c) | Keep state between calls | Counter increments | Static local |
| 03 | [ex03_global_static.c](solutions/ex03_global_static.c) | File-scope driver state | Init/read state | Static global |
| 04 | [ex04_const_rodata.c](solutions/ex04_const_rodata.c) | Use const lookup table | Table values printed | .rodata |
| 05 | [ex05_heap_malloc_free.c](solutions/ex05_heap_malloc_free.c) | Allocate/free buffer | Heap buffer filled | malloc/free |
| 06 | [ex06_malloc_failure.c](solutions/ex06_malloc_failure.c) | Check allocation failure | Safe error handling | NULL check |
| 07 | [ex07_stack_buffer_risk.c](solutions/ex07_stack_buffer_risk.c) | Compare stack buffer sizes | Safer small buffer | Stack sizing |
| 08 | [ex08_memory_copy.c](solutions/ex08_memory_copy.c) | Copy bytes safely | Destination copied | memcpy |
| 09 | [ex09_memory_set.c](solutions/ex09_memory_set.c) | Clear a packet | Zeroed struct | memset |
| 10 | [ex10_pool_allocator.c](solutions/ex10_pool_allocator.c) | Fixed block allocator | Blocks allocated/freed | Memory pool |
| 11 | [ex11_leak_demo.c](solutions/ex11_leak_demo.c) | Demonstrate ownership | Free after use | Leak prevention |
| 12 | [ex12_embedded_memory_map.c](solutions/ex12_embedded_memory_map.c) | Print simulated memory map | Regions listed | Firmware memory |

---

## Build & Run

```bash
cd c_practice/topic_11_memory/solutions
gcc ex01_stack_local.c -o ex01 && ./ex01
```
