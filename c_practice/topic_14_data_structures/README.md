# Topic 14 - Data Structures

Embedded systems use small, predictable data structures: arrays, queues, ring buffers, linked lists, stacks, and tables. Fixed capacity is often better than dynamic allocation.

## Brief Theory

| Structure | Strength | Embedded use |
|-----------|----------|--------------|
| Ring buffer | FIFO with fixed memory | UART RX/TX buffering |
| Stack | Last-in first-out | Parser nesting, undo |
| Linked list | Insert/remove nodes | Driver registries |
| Table | Fast lookup | Commands, configs |
| Queue | Ordered events | Task communication |

**Tips:** Keep capacity explicit. Return success/failure on push operations. In ISR/shared contexts, protect head/tail updates.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_fixed_array_table.c](solutions/ex01_fixed_array_table.c) | Iterate config table | Rows printed | Table |
| 02 | [ex02_linear_search.c](solutions/ex02_linear_search.c) | Find item by ID | Match found | Search |
| 03 | [ex03_stack_push_pop.c](solutions/ex03_stack_push_pop.c) | Fixed integer stack | LIFO output | Stack |
| 04 | [ex04_queue_basic.c](solutions/ex04_queue_basic.c) | Fixed FIFO queue | FIFO output | Queue |
| 05 | [ex05_ring_buffer_bytes.c](solutions/ex05_ring_buffer_bytes.c) | Byte ring buffer | Bytes popped | Ring buffer |
| 06 | [ex06_ring_buffer_full_empty.c](solutions/ex06_ring_buffer_full_empty.c) | Full/empty checks | Overflow rejected | Bounds |
| 07 | [ex07_singly_linked_list.c](solutions/ex07_singly_linked_list.c) | Link static nodes | List printed | Linked list |
| 08 | [ex08_list_insert_front.c](solutions/ex08_list_insert_front.c) | Push node to front | Reverse order | Insert |
| 09 | [ex09_list_remove_value.c](solutions/ex09_list_remove_value.c) | Remove matching node | Value removed | Delete |
| 10 | [ex10_lookup_table.c](solutions/ex10_lookup_table.c) | Lookup code to string | Name printed | LUT |
| 11 | [ex11_event_queue.c](solutions/ex11_event_queue.c) | Queue event structs | Events handled | Event queue |
| 12 | [ex12_uart_rx_ring.c](solutions/ex12_uart_rx_ring.c) | Simulate UART RX FIFO | Line received | UART ring |

---

## Build & Run

```bash
cd c_practice/topic_14_data_structures/solutions
gcc ex01_fixed_array_table.c -o ex01 && ./ex01
```
