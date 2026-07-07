/* Number of ways to climb n stairs using 1 or 2 steps. */
#include <stdio.h>

int main(void)
{
    int n = 5;
    int dp[6] = {1, 1};
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
    printf("ways=%d\n", dp[n]);
    return 0;
}
