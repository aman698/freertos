# Topic 05 — Pointers

Pointers are central to embedded C: buffers, registers, callbacks, and hardware structs all use addresses. Master `&`, `*`, NULL checks, and pointer arithmetic before touching MMIO.

## Brief Theory

| Concept | Syntax | Embedded use |
|---------|--------|--------------|
| Address-of | `&var` | Pass buffer to driver |
| Dereference | `*ptr` | Read/write through pointer |
| NULL | `NULL` / `0` | Guard invalid pointers |
| Pointer arithmetic | `ptr + 1` | Walk byte buffer, array |
| `const` pointer | `const T *p`, `T *const p` | Read-only flash table vs fixed MMIO |
| `void *` | Generic address | DMA, memcpy-style APIs |
| Struct pointer | `->` | Register map, device handle |

**Tips:** Always check for NULL before dereference. Pointer arithmetic scales by pointed-to type size. Never return address of local stack variable.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_address_of.c](solutions/ex01_address_of.c) | Print variable address with `&` | Hex address shown | Address-of |
| 02 | [ex02_dereference.c](solutions/ex02_dereference.c) | Read/write through `*` | Value updated via ptr | Dereference |
| 03 | [ex03_null_check.c](solutions/ex03_null_check.c) | Guard NULL before use | Safe skip message | NULL check |
| 04 | [ex04_pointer_arithmetic.c](solutions/ex04_pointer_arithmetic.c) | Walk byte buffer with `ptr++` | Each byte printed | Ptr arithmetic |
| 05 | [ex05_const_pointer.c](solutions/ex05_const_pointer.c) | `const` data vs const pointer | Const rules demo | const pointers |
| 06 | [ex06_pointer_to_pointer.c](solutions/ex06_pointer_to_pointer.c) | Double pointer out-param | Indirect update | `**` |
| 07 | [ex07_void_pointer.c](solutions/ex07_void_pointer.c) | Cast `void*` to typed ptr | Bytes copied | void* |
| 08 | [ex08_struct_pointer.c](solutions/ex08_struct_pointer.c) | Access fields with `->` | Struct via pointer | struct-> |
| 09 | [ex09_array_pointer.c](solutions/ex09_array_pointer.c) | Array name decays to pointer | Index via pointer | Array/pointer |
| 10 | [ex10_return_static_ptr.c](solutions/ex10_return_static_ptr.c) | Return pointer to static buf | Valid persistent ptr | Static storage |
| 11 | [ex11_pointer_comparison.c](solutions/ex11_pointer_comparison.c) | Compare ptr to range end | Loop until end | Ptr compare |
| 12 | [ex12_embedded_buffer_ptr.c](solutions/ex12_embedded_buffer_ptr.c) | UART TX via pointer+length | Buffer sent | Buffer pointer |

---

## Build & Run

```bash
cd c_practice/topic_05_pointers/solutions
gcc ex01_address_of.c -o ex01 && ./ex01
```
