/* O(n^2) longest increasing subsequence length. */
#include <stdio.h>

int main(void)
{
    int a[] = {10, 9, 2, 5, 3, 7};
    int dp[6], best = 1;
    for (int i = 0; i < 6; i++) dp[i] = 1;
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < i; j++) if (a[j] < a[i] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
        if (dp[i] > best) best = dp[i];
    }
    printf("lis=%d\n", best);
    return 0;
}
