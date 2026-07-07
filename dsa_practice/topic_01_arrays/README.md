# Topic 01 - Arrays

Arrays store same-type values in contiguous memory. Indexing is O(1), traversal is O(n), insert/delete in the middle is O(n).

## Brief Theory

| Concept | Use |
|---------|-----|
| Traversal | Visit every element |
| Min/max | Track best value so far |
| Prefix sum | Fast range sum after preprocessing |
| Two pointers | Work from both ends |
| Rotation | Move elements while preserving order |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_traverse_sum.c](solutions/ex01_traverse_sum.c) | Sum array elements | Traversal |
| 02 | [ex02_min_max.c](solutions/ex02_min_max.c) | Find min and max | Scan |
| 03 | [ex03_reverse_array.c](solutions/ex03_reverse_array.c) | Reverse in place | Two pointers |
| 04 | [ex04_second_largest.c](solutions/ex04_second_largest.c) | Find second largest | Tracking |
| 05 | [ex05_prefix_sum.c](solutions/ex05_prefix_sum.c) | Build prefix sum | Preprocessing |
| 06 | [ex06_range_sum.c](solutions/ex06_range_sum.c) | Query range sum | Prefix query |
| 07 | [ex07_left_rotate.c](solutions/ex07_left_rotate.c) | Rotate left by one | Shifting |
| 08 | [ex08_remove_duplicates.c](solutions/ex08_remove_duplicates.c) | Deduplicate sorted array | Write index |
| 09 | [ex09_merge_sorted.c](solutions/ex09_merge_sorted.c) | Merge two sorted arrays | Merge |
| 10 | [ex10_max_subarray.c](solutions/ex10_max_subarray.c) | Maximum subarray sum | Kadane |
