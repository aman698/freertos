/* Count connected components with DFS. */
#include <stdio.h>

static int g[4][4] = {{0,1,0,0},{1,0,0,0},{0,0,0,1},{0,0,1,0}};
static int seen[4];

static void dfs(int v)
{
    seen[v] = 1;
    for (int to = 0; to < 4; to++) if (g[v][to] && !seen[to]) dfs(to);
}

int main(void)
{
    int components = 0;
    for (int v = 0; v < 4; v++) if (!seen[v]) { components++; dfs(v); }
    printf("components=%d\n", components);
    return 0;
}
