/* Recursive DFS over adjacency matrix. */
#include <stdio.h>

static int g[4][4] = {{0,1,1,0},{1,0,0,0},{1,0,0,1},{0,0,1,0}};
static int seen[4];

static void dfs(int v)
{
    seen[v] = 1;
    printf("%d ", v);
    for (int to = 0; to < 4; to++) if (g[v][to] && !seen[to]) dfs(to);
}

int main(void)
{
    dfs(0); putchar('\n');
    return 0;
}
