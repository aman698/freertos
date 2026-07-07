/* Minimum coins to make amount. */
#include <stdio.h>

static int min(int a, int b) { return a < b ? a : b; }

int main(void)
{
    int coins[] = {1, 3, 4};
    int dp[7];
    for (int i = 0; i <= 6; i++) dp[i] = 99;
    dp[0] = 0;
    for (int amt = 1; amt <= 6; amt++) {
        for (int c = 0; c < 3; c++) if (coins[c] <= amt) dp[amt] = min(dp[amt], 1 + dp[amt - coins[c]]);
    }
    printf("min_coins=%d\n", dp[6]);
    return 0;
}
