/* Count paths in grid moving only right or down. */
#include <stdio.h>

int main(void)
{
    int dp[3][3] = {{0}};
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (r == 0 || c == 0) dp[r][c] = 1;
            else dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
        }
    }
    printf("paths=%d\n", dp[2][2]);
    return 0;
}
