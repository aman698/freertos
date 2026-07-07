# FreeRTOS Interview Preparation Map

Use this project as a 4-layer interview prep system:

1. **Embedded C base** - `c_practice/`
2. **DSA/problem solving** - `dsa_practice/`
3. **FreeRTOS concepts** - `examples/` + `THEORY_REFERENCE.md`
4. **Integrated firmware design** - `projects/Advanced_FreeRTOS_Lab/`

---

## What To Master First

| Priority | Topic | Must explain in interview |
|----------|-------|---------------------------|
| 1 | Tasks | Ready, running, blocked, suspended states |
| 2 | Scheduling | Priority, preemption, time slicing, starvation |
| 3 | Queue | FIFO data transfer, ISR-safe send, blocking timeout |
| 4 | Semaphore | Binary signal vs counting resource pool |
| 5 | Mutex | Ownership and priority inheritance |
| 6 | ISR deferral | ISR gives queue/semaphore/notify, task does work |
| 7 | Timer | Timer service task, short callbacks |
| 8 | Memory | Heap, per-task stack, high-water mark |
| 9 | Event group | Bit flags, wait-all vs wait-any |
| 10 | Task notification | Lightweight one-task signal |

---

## Interview Build Order

| Stage | Practice | Goal |
|-------|----------|------|
| 1 | `examples/01_basic_multi_task` | Create two tasks from memory |
| 2 | `examples/02_queue_button_led` | Explain ISR -> queue -> debounce task |
| 3 | `examples/03_mutex_uart_printf` | Prove why UART needs a mutex |
| 4 | `examples/04_timer_semaphore_isr` | Compare timer and binary semaphore |
| 5 | `examples/07_uart_isr_queue` | Implement UART ISR byte queue |
| 6 | `examples/08_event_groups` | Wait for multiple system-ready bits |
| 7 | `examples/09_task_notifications` | Replace semaphore with task notification |
| 8 | `examples/10_stream_buffer` | Build line-based UART CLI |
| 9 | `examples/12_deadlock_demo` | Identify and fix deadlock |
| 10 | `projects/Advanced_FreeRTOS_Lab` | Explain full architecture |

---

## Oral Questions To Practice

1. What happens after `osKernelStart()`?
2. Why should a task call `osDelay()` instead of spinning?
3. Queue vs semaphore vs mutex: when do you use each?
4. What APIs are safe inside an ISR?
5. Why is `printf` bad inside an ISR?
6. What is priority inversion, and how does a mutex help?
7. What causes stack overflow in an RTOS task?
8. How do you measure free heap and task stack margin?
9. Why can a high-priority task starve lower-priority tasks?
10. How would you design a UART command parser with FreeRTOS?
11. What is a stream buffer, and how is it different from a queue?
12. What is static allocation, and why is it used in production firmware?
13. How do you detect deadlock?
14. What is tickless idle?
15. How would you debug a hard fault caused by an RTOS task?

---

## Coding Drills

Do these without looking at existing code:

| Drill | Target time |
|-------|-------------|
| Create LED blink task | 10 min |
| Create queue producer/consumer | 15 min |
| Send button event from EXTI ISR to task | 20 min |
| Add mutex-safe UART print | 20 min |
| Add task notification from ISR | 15 min |
| Add event group system-ready wait | 20 min |
| Add stream buffer line parser | 30 min |
| Add stack monitor task | 25 min |
| Fix deadlock by lock ordering | 15 min |
| Explain capstone task diagram | 5 min |

---

## Resume Project Summary

Use this wording in an interview:

> I built a FreeRTOS practice firmware set on STM32F411RE covering tasks, queues, semaphores, mutexes, software timers, event groups, task notifications, stream buffers, queue sets, static allocation, stack monitoring, ISR deferral, and deadlock debugging. The capstone combines UART CLI, sensor queue, event flags, monitor task, and modular app code.

---

## Final Checklist

- [ ] I can draw every task and queue in Example 02.
- [ ] I can write `xQueueSendFromISR` and `portYIELD_FROM_ISR` from memory.
- [ ] I can explain why mutex is not a binary semaphore.
- [ ] I can measure stack high-water mark.
- [ ] I can explain one real deadlock and its fix.
- [ ] I can build a UART CLI using queue or stream buffer.
- [ ] I can explain why static allocation is useful.
- [ ] I can walk through the capstone architecture in 5 minutes.
