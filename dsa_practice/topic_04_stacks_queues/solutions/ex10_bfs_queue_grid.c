/* BFS on tiny grid using a queue. */
#include <stdio.h>

typedef struct { int r, c, d; } Cell;

int main(void)
{
    int seen[2][2] = {{0}};
    Cell q[4] = {{0, 0, 0}};
    int head = 0, tail = 1;
    seen[0][0] = 1;
    while (head < tail) {
        Cell x = q[head++];
        if (x.r == 1 && x.c == 1) printf("dist=%d\n", x.d);
        if (x.r + 1 < 2 && !seen[x.r + 1][x.c]) { seen[x.r + 1][x.c] = 1; q[tail++] = (Cell){x.r + 1, x.c, x.d + 1}; }
        if (x.c + 1 < 2 && !seen[x.r][x.c + 1]) { seen[x.r][x.c + 1] = 1; q[tail++] = (Cell){x.r, x.c + 1, x.d + 1}; }
    }
    return 0;
}
