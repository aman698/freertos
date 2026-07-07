/* Build and print adjacency matrix. */
#include <stdio.h>

int main(void)
{
    int g[3][3] = {{0}};
    g[0][1] = g[1][0] = 1;
    g[1][2] = g[2][1] = 1;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) printf("%d ", g[r][c]);
        putchar('\n');
    }
    return 0;
}
