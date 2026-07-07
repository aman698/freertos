# Topic 10 - Dynamic Programming

Dynamic programming solves overlapping subproblems once and reuses their answers. It appears in optimization, counting, and sequence problems.

## Brief Theory

| Concept | Use |
|---------|-----|
| State | Meaning of `dp[i]` |
| Transition | How to compute next state |
| Base case | Known starting value |
| Memoization | Top-down cache |
| Tabulation | Bottom-up table |

---

## Exercises

| # | File | Problem | Key Concept |
|---|------|---------|-------------|
| 01 | [ex01_fibonacci_dp.c](solutions/ex01_fibonacci_dp.c) | Fibonacci tabulation | 1D DP |
| 02 | [ex02_climbing_stairs.c](solutions/ex02_climbing_stairs.c) | Ways to climb stairs | Recurrence |
| 03 | [ex03_min_cost_stairs.c](solutions/ex03_min_cost_stairs.c) | Minimum stair cost | Optimization |
| 04 | [ex04_coin_change_ways.c](solutions/ex04_coin_change_ways.c) | Count coin ways | Unbounded DP |
| 05 | [ex05_coin_change_min.c](solutions/ex05_coin_change_min.c) | Minimum coins | Min DP |
| 06 | [ex06_knapsack_01.c](solutions/ex06_knapsack_01.c) | 0/1 knapsack | 2D DP |
| 07 | [ex07_lcs_length.c](solutions/ex07_lcs_length.c) | Longest common subsequence | String DP |
| 08 | [ex08_edit_distance.c](solutions/ex08_edit_distance.c) | Edit distance | 2D DP |
| 09 | [ex09_longest_increasing_subsequence.c](solutions/ex09_longest_increasing_subsequence.c) | LIS length | Sequence DP |
| 10 | [ex10_grid_paths.c](solutions/ex10_grid_paths.c) | Count grid paths | Grid DP |
