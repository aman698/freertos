/* Longest common subsequence length. */
#include <stdio.h>
#include <string.h>

static int max(int a, int b) { return a > b ? a : b; }

int main(void)
{
    const char *a = "abcde", *b = "ace";
    int dp[6][4] = {{0}};
    for (size_t i = 1; i <= strlen(a); i++) {
        for (size_t j = 1; j <= strlen(b); j++) {
            dp[i][j] = (a[i - 1] == b[j - 1]) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    printf("lcs=%d\n", dp[strlen(a)][strlen(b)]);
    return 0;
}
