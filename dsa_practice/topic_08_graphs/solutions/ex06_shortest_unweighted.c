/* Shortest path distance in unweighted graph using BFS. */
#include <stdio.h>

int main(void)
{
    int g[4][4] = {{0,1,1,0},{1,0,0,1},{1,0,0,0},{0,1,0,0}};
    int dist[4] = {0, -1, -1, -1}, q[4] = {0}, head = 0, tail = 1;
    while (head < tail) {
        int v = q[head++];
        for (int to = 0; to < 4; to++) if (g[v][to] && dist[to] == -1) {
            dist[to] = dist[v] + 1; q[tail++] = to;
        }
    }
    printf("dist_to_3=%d\n", dist[3]);
    return 0;
}
