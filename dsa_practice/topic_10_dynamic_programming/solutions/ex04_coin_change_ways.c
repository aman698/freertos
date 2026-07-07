/* Count ways to make amount with unlimited coins. */
#include <stdio.h>

int main(void)
{
    int coins[] = {1, 2, 5};
    int dp[6] = {1, 0, 0, 0, 0, 0};
    for (int c = 0; c < 3; c++) {
        for (int amt = coins[c]; amt <= 5; amt++) dp[amt] += dp[amt - coins[c]];
    }
    printf("ways=%d\n", dp[5]);
    return 0;
}
