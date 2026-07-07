# Topic 09 - Hashing

Hashing maps keys to array indices. It gives average O(1) insert/search when the hash function distributes keys well and collisions are handled.

## Brief Theory

| Concept | Use |
|---------|-----|
| Hash function | Convert key to index |
| Collision | Two keys same index |
| Chaining | Store list per bucket |
| Open addressing | Probe next slot |
| Frequency table | Count occurrences |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_int_frequency.c](solutions/ex01_int_frequency.c) | Count small integers | Frequency |
| 02 | [ex02_char_frequency.c](solutions/ex02_char_frequency.c) | Count characters | ASCII table |
| 03 | [ex03_first_repeating.c](solutions/ex03_first_repeating.c) | First repeated value | Seen set |
| 04 | [ex04_two_sum.c](solutions/ex04_two_sum.c) | Pair with target sum | Hash set idea |
| 05 | [ex05_simple_hash.c](solutions/ex05_simple_hash.c) | Hash integers to buckets | Mod hash |
| 06 | [ex06_linear_probing.c](solutions/ex06_linear_probing.c) | Insert with probing | Open addressing |
| 07 | [ex07_chaining.c](solutions/ex07_chaining.c) | Collision chaining | Buckets |
| 08 | [ex08_string_hash.c](solutions/ex08_string_hash.c) | Hash string | Polynomial hash |
| 09 | [ex09_unique_count.c](solutions/ex09_unique_count.c) | Count unique small ints | Set |
| 10 | [ex10_longest_distinct_window.c](solutions/ex10_longest_distinct_window.c) | Longest distinct substring | Sliding window |
