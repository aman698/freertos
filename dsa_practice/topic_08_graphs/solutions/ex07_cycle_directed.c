/* Detect directed cycle with recursion stack. */
#include <stdbool.h>
#include <stdio.h>

static int g[3][3] = {{0,1,0},{0,0,1},{1,0,0}};
static int seen[3], active[3];

static bool dfs(int v)
{
    seen[v] = active[v] = 1;
    for (int to = 0; to < 3; to++) if (g[v][to]) {
        if (!seen[to] && dfs(to)) return true;
        if (active[to]) return true;
    }
    active[v] = 0;
    return false;
}

int main(void)
{
    printf("cycle=%s\n", dfs(0) ? "yes" : "no");
    return 0;
}
