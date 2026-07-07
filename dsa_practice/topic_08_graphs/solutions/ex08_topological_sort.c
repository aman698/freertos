/* Topological sort with DFS finish order. */
#include <stdio.h>

static int g[4][4] = {{0,1,1,0},{0,0,0,1},{0,0,0,1},{0,0,0,0}};
static int seen[4], order[4], k;

static void dfs(int v)
{
    seen[v] = 1;
    for (int to = 0; to < 4; to++) if (g[v][to] && !seen[to]) dfs(to);
    order[k++] = v;
}

int main(void)
{
    for (int v = 0; v < 4; v++) if (!seen[v]) dfs(v);
    for (int i = 3; i >= 0; i--) printf("%d ", order[i]);
    putchar('\n');
    return 0;
}
