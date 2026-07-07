/* Edit distance with insert/delete/replace. */
#include <stdio.h>
#include <string.h>

static int min3(int a, int b, int c) { int m = a < b ? a : b; return m < c ? m : c; }

int main(void)
{
    const char *a = "cat", *b = "cut";
    int dp[4][4];
    for (int i = 0; i <= 3; i++) dp[i][0] = i;
    for (int j = 0; j <= 3; j++) dp[0][j] = j;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            int cost = a[i - 1] == b[j - 1] ? 0 : 1;
            dp[i][j] = min3(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost);
        }
    }
    printf("distance=%d\n", dp[strlen(a)][strlen(b)]);
    return 0;
}
