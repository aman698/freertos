/* Minimum cost to reach top of stairs. */
#include <stdio.h>

static int min(int a, int b) { return a < b ? a : b; }

int main(void)
{
    int cost[] = {10, 15, 20};
    int dp[4] = {0};
    for (int i = 2; i <= 3; i++) dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    printf("min_cost=%d\n", dp[3]);
    return 0;
}
