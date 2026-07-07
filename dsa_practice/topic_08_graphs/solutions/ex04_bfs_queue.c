/* BFS traversal using a queue. */
#include <stdio.h>

int main(void)
{
    int g[4][4] = {{0,1,1,0},{1,0,0,1},{1,0,0,0},{0,1,0,0}};
    int seen[4] = {1,0,0,0}, q[4] = {0}, head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        printf("%d ", v);
        for (int to = 0; to < 4; to++) if (g[v][to] && !seen[to]) {
            seen[to] = 1; q[tail++] = to;
        }
    }
    putchar('\n');
    return 0;
}
