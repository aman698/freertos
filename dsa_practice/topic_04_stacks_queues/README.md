# Topic 04 - Stacks and Queues

Stacks are LIFO. Queues are FIFO. Both are often implemented with fixed arrays in embedded C for predictable memory use.

## Brief Theory

| Structure | Rule | Use |
|-----------|------|-----|
| Stack | Last in, first out | Expression parsing, DFS |
| Queue | First in, first out | BFS, event queues |
| Circular queue | Head/tail wrap | Ring buffers |
| Deque | Both ends | Sliding window |
| Monotonic stack | Ordered stack | Next greater element |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_stack_array.c](solutions/ex01_stack_array.c) | Array stack | Push/pop |
| 02 | [ex02_balanced_parentheses.c](solutions/ex02_balanced_parentheses.c) | Match brackets | Stack use |
| 03 | [ex03_queue_array.c](solutions/ex03_queue_array.c) | Array queue | FIFO |
| 04 | [ex04_circular_queue.c](solutions/ex04_circular_queue.c) | Circular queue | Wraparound |
| 05 | [ex05_deque_basic.c](solutions/ex05_deque_basic.c) | Basic deque | Two ends |
| 06 | [ex06_next_greater.c](solutions/ex06_next_greater.c) | Next greater element | Monotonic stack |
| 07 | [ex07_postfix_eval.c](solutions/ex07_postfix_eval.c) | Evaluate postfix | Operand stack |
| 08 | [ex08_queue_using_stacks.c](solutions/ex08_queue_using_stacks.c) | Queue with two stacks | Transfer |
| 09 | [ex09_stack_min.c](solutions/ex09_stack_min.c) | Stack with min | Auxiliary stack |
| 10 | [ex10_bfs_queue_grid.c](solutions/ex10_bfs_queue_grid.c) | Grid BFS queue | BFS |
