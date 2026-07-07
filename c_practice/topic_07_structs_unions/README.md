# Topic 07 — Structs & Unions

Structs group related fields (sensor reading, register block). Unions share storage for type punning. Bitfields pack flags into minimal space — common in register headers.

## Brief Theory

| Feature | Purpose | Embedded use |
|---------|---------|--------------|
| `struct` | Named fields, ordered layout | Device config, packet format |
| Padding | Alignment gaps between members | `sizeof` may exceed sum of fields |
| `typedef struct` | Shorter type name | `gpio_handle_t` |
| `union` | Overlapping members | Float/int view, byte/word access |
| Bitfields | Sub-byte fields | Control register flags |

**Tips:** Use `#pragma pack` sparingly — alignment affects atomic access. Prefer CMSIS-style structs for registers. Document endianness for wire-format structs.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_basic_struct.c](solutions/ex01_basic_struct.c) | Define and print struct fields | Sensor struct values | Basic struct |
| 02 | [ex02_typedef_struct.c](solutions/ex02_typedef_struct.c) | typedef struct alias | Cleaner type name | typedef |
| 03 | [ex03_struct_init.c](solutions/ex03_struct_init.c) | Designated initializer | Fields set at define | Init syntax |
| 04 | [ex04_struct_padding.c](solutions/ex04_struct_padding.c) | Show padding with sizeof | Padding bytes revealed | Alignment |
| 05 | [ex05_struct_array.c](solutions/ex05_struct_array.c) | Array of sensor structs | Multiple readings | Struct array |
| 06 | [ex06_nested_struct.c](solutions/ex06_nested_struct.c) | Struct inside struct | Nested access | Nesting |
| 07 | [ex07_union_basic.c](solutions/ex07_union_basic.c) | Union shares storage | Same bytes, two views | Union |
| 08 | [ex08_union_bytes.c](solutions/ex08_union_bytes.c) | Access uint32 as bytes | Byte order shown | Type punning |
| 09 | [ex09_bitfield_intro.c](solutions/ex09_bitfield_intro.c) | Bitfield flags struct | Individual bits set | Bitfields |
| 10 | [ex10_sensor_packet.c](solutions/ex10_sensor_packet.c) | Wire-format packet struct | Packed fields printed | Protocol struct |
| 11 | [ex11_register_struct.c](solutions/ex11_register_struct.c) | GPIO register struct map | CR/ODR/IDR layout | Register struct |
| 12 | [ex12_config_struct.c](solutions/ex12_config_struct.c) | Device config with defaults | Config dump | Config pattern |

---

## Build & Run

```bash
cd c_practice/topic_07_structs_unions/solutions
gcc ex01_basic_struct.c -o ex01 && ./ex01
```
