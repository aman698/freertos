/* Queue using two stacks: push to input, pop from output. */
#include <stdio.h>

int main(void)
{
    int in[4], out[4], itop = 0, otop = 0;
    in[itop++] = 1; in[itop++] = 2;
    while (itop > 0) out[otop++] = in[--itop];
    printf("%d %d\n", out[--otop], out[--otop]);
    return 0;
}
