# Topic 03 - Linked Lists

A linked list stores data in nodes connected by pointers. It supports cheap insertion/removal when you already have the node position, but traversal is O(n).

## Brief Theory

| Concept | Use |
|---------|-----|
| Node | Data plus `next` pointer |
| Head | First node in list |
| Insert front | O(1) insertion |
| Delete | Relink around target node |
| Reverse | Rewire `next` pointers |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_create_traverse.c](solutions/ex01_create_traverse.c) | Create static list | Traversal |
| 02 | [ex02_count_nodes.c](solutions/ex02_count_nodes.c) | Count nodes | Length |
| 03 | [ex03_search_value.c](solutions/ex03_search_value.c) | Search value | Linear search |
| 04 | [ex04_insert_front.c](solutions/ex04_insert_front.c) | Insert at front | Head update |
| 05 | [ex05_insert_end.c](solutions/ex05_insert_end.c) | Insert at end | Tail traversal |
| 06 | [ex06_delete_value.c](solutions/ex06_delete_value.c) | Delete value | Relink |
| 07 | [ex07_reverse_list.c](solutions/ex07_reverse_list.c) | Reverse linked list | Pointer rewiring |
| 08 | [ex08_middle_node.c](solutions/ex08_middle_node.c) | Find middle node | Slow/fast |
| 09 | [ex09_detect_cycle.c](solutions/ex09_detect_cycle.c) | Detect cycle | Floyd algorithm |
| 10 | [ex10_merge_sorted_lists.c](solutions/ex10_merge_sorted_lists.c) | Merge sorted lists | Pointer merge |
