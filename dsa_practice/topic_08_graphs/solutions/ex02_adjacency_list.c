/* Adjacency list with static arrays. */
#include <stdio.h>

int main(void)
{
    int adj[3][2] = {{1, -1}, {0, 2}, {1, -1}};
    for (int v = 0; v < 3; v++) {
        printf("%d:", v);
        for (int i = 0; i < 2 && adj[v][i] != -1; i++) printf(" %d", adj[v][i]);
        putchar('\n');
    }
    return 0;
}
