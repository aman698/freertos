/* 0/1 knapsack maximum value. */
#include <stdio.h>

static int max(int a, int b) { return a > b ? a : b; }

int main(void)
{
    int wt[] = {2, 3, 4}, val[] = {4, 5, 6};
    int dp[4][6] = {{0}};
    for (int i = 1; i <= 3; i++) {
        for (int cap = 0; cap <= 5; cap++) {
            dp[i][cap] = dp[i - 1][cap];
            if (wt[i - 1] <= cap) dp[i][cap] = max(dp[i][cap], val[i - 1] + dp[i - 1][cap - wt[i - 1]]);
        }
    }
    printf("best=%d\n", dp[3][5]);
    return 0;
}
