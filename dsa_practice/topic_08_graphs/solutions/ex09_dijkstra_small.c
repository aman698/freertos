/* Dijkstra on a tiny weighted graph. */
#include <limits.h>
#include <stdio.h>

int main(void)
{
    int g[3][3] = {{0,4,1},{4,0,2},{1,2,0}};
    int dist[3] = {0, INT_MAX, INT_MAX}, used[3] = {0};
    for (int step = 0; step < 3; step++) {
        int v = -1;
        for (int i = 0; i < 3; i++) if (!used[i] && (v == -1 || dist[i] < dist[v])) v = i;
        used[v] = 1;
        for (int to = 0; to < 3; to++) if (g[v][to] && dist[v] + g[v][to] < dist[to]) dist[to] = dist[v] + g[v][to];
    }
    printf("dist_to_1=%d\n", dist[1]);
    return 0;
}
