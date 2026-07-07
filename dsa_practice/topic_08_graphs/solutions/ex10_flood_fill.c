/* Flood fill connected cells in a grid. */
#include <stdio.h>

static int grid[3][3] = {{1,1,0},{1,0,0},{0,0,1}};

static void fill(int r, int c)
{
    if (r < 0 || c < 0 || r >= 3 || c >= 3 || grid[r][c] != 1) return;
    grid[r][c] = 2;
    fill(r + 1, c); fill(r - 1, c); fill(r, c + 1); fill(r, c - 1);
}

int main(void)
{
    fill(0, 0);
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) printf("%d ", grid[r][c]);
        putchar('\n');
    }
    return 0;
}
