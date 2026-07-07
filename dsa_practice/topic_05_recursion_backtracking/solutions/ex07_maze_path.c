/* DFS backtracking path in a small maze. */
#include <stdbool.h>
#include <stdio.h>

static int maze[3][3] = {{1, 1, 0}, {0, 1, 0}, {0, 1, 1}};
static int path[3][3];

static bool dfs(int r, int c)
{
    if (r < 0 || c < 0 || r >= 3 || c >= 3 || maze[r][c] == 0 || path[r][c]) return false;
    path[r][c] = 1;
    if (r == 2 && c == 2) return true;
    if (dfs(r + 1, c) || dfs(r, c + 1) || dfs(r - 1, c) || dfs(r, c - 1)) return true;
    path[r][c] = 0;
    return false;
}

int main(void)
{
    printf("path=%s\n", dfs(0, 0) ? "yes" : "no");
    return 0;
}
