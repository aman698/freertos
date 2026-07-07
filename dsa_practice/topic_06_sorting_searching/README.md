# Topic 06 - Sorting and Searching

Searching finds data. Sorting arranges data so later operations become easier. Learn both simple O(n^2) sorts and faster divide-and-conquer sorts.

## Brief Theory

| Algorithm | Time | Note |
|-----------|------|------|
| Linear search | O(n) | Works unsorted |
| Binary search | O(log n) | Needs sorted array |
| Bubble/selection/insertion | O(n^2) | Good for learning |
| Merge sort | O(n log n) | Stable, extra memory |
| Quick sort | Average O(n log n) | In-place partition |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_linear_search.c](solutions/ex01_linear_search.c) | Linear search | O(n) |
| 02 | [ex02_binary_search_iter.c](solutions/ex02_binary_search_iter.c) | Binary search | O(log n) |
| 03 | [ex03_bubble_sort.c](solutions/ex03_bubble_sort.c) | Bubble sort | Adjacent swap |
| 04 | [ex04_selection_sort.c](solutions/ex04_selection_sort.c) | Selection sort | Select min |
| 05 | [ex05_insertion_sort.c](solutions/ex05_insertion_sort.c) | Insertion sort | Shift insert |
| 06 | [ex06_merge_sort.c](solutions/ex06_merge_sort.c) | Merge sort | Divide/merge |
| 07 | [ex07_quick_sort.c](solutions/ex07_quick_sort.c) | Quick sort | Partition |
| 08 | [ex08_counting_sort.c](solutions/ex08_counting_sort.c) | Counting sort | Frequency |
| 09 | [ex09_lower_bound.c](solutions/ex09_lower_bound.c) | First >= target | Binary boundary |
| 10 | [ex10_search_rotated.c](solutions/ex10_search_rotated.c) | Search rotated sorted | Modified binary |
