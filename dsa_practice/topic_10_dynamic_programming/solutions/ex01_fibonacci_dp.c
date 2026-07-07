/* Fibonacci with bottom-up DP. */
#include <stdio.h>

int main(void)
{
    int dp[8] = {0, 1};
    for (int i = 2; i < 8; i++) dp[i] = dp[i - 1] + dp[i - 2];
    printf("fib(7)=%d\n", dp[7]);
    return 0;
}
