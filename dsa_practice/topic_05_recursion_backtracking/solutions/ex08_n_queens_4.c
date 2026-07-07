/* Count solutions for 4-queens. */
#include <stdbool.h>
#include <stdio.h>

static int col[4];

static bool safe(int row, int c)
{
    for (int r = 0; r < row; r++) {
        if (col[r] == c || row - r == c - col[r] || row - r == col[r] - c) return false;
    }
    return true;
}

static int solve(int row)
{
    if (row == 4) return 1;
    int count = 0;
    for (int c = 0; c < 4; c++) {
        if (safe(row, c)) {
            col[row] = c;
            count += solve(row + 1);
        }
    }
    return count;
}

int main(void)
{
    printf("solutions=%d\n", solve(0));
    return 0;
}
