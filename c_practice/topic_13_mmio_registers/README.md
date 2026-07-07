# Topic 13 - MMIO Registers

Memory-mapped I/O exposes peripheral registers at fixed addresses. Firmware reads and writes those addresses through `volatile` objects or register-structure overlays.

## Brief Theory

| Concept | Pattern | Embedded use |
|---------|---------|--------------|
| MMIO register | `*(volatile uint32_t *)addr` | Direct hardware access |
| Register bit | `reg |= BIT(n)` | Enable peripheral feature |
| Field write | clear mask, then OR value | Configure modes |
| Struct overlay | `GPIO_TypeDef *GPIOA` | Peripheral register map |
| Read-modify-write | read, edit, write | Risky if ISR also writes |

**Tips:** Use `volatile` for hardware registers. Do not dereference real MCU addresses on a PC. These exercises simulate registers with normal variables.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_register_variable.c](solutions/ex01_register_variable.c) | Simulate register read/write | Register value printed | MMIO idea |
| 02 | [ex02_set_clear_bits.c](solutions/ex02_set_clear_bits.c) | Set and clear control bits | Bit states printed | Bit ops |
| 03 | [ex03_gpio_output_sim.c](solutions/ex03_gpio_output_sim.c) | Toggle GPIO output bit | ODR changes | GPIO ODR |
| 04 | [ex04_field_write.c](solutions/ex04_field_write.c) | Write bit field safely | Field configured | Mask/shift |
| 05 | [ex05_register_struct_overlay.c](solutions/ex05_register_struct_overlay.c) | Use register-map struct | GPIO registers set | Struct overlay |
| 06 | [ex06_read_modify_write.c](solutions/ex06_read_modify_write.c) | Preserve unrelated bits | Register merged | RMW |
| 07 | [ex07_status_poll.c](solutions/ex07_status_poll.c) | Poll status flag | Ready detected | Status flag |
| 08 | [ex08_write_one_to_clear.c](solutions/ex08_write_one_to_clear.c) | Clear flags with W1C mask | Flag cleared | W1C |
| 09 | [ex09_reserved_bits.c](solutions/ex09_reserved_bits.c) | Avoid reserved-bit writes | Reserved preserved | Register safety |
| 10 | [ex10_brr_set_reset.c](solutions/ex10_brr_set_reset.c) | Atomic GPIO set/reset model | Pin state changes | BSRR/BRR |
| 11 | [ex11_clock_enable_order.c](solutions/ex11_clock_enable_order.c) | Enable clock before GPIO | Init sequence printed | RCC order |
| 12 | [ex12_uart_register_init.c](solutions/ex12_uart_register_init.c) | Simulate UART register init | CR/BRR values | Peripheral init |

---

## Build & Run

```bash
cd c_practice/topic_13_mmio_registers/solutions
gcc ex01_register_variable.c -o ex01 && ./ex01
```
