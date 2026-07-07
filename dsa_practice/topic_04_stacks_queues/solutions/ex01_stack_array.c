/* Fixed-size array stack. */
#include <stdbool.h>
#include <stdio.h>

#define CAP 4
typedef struct { int data[CAP]; int top; } Stack;

static bool push(Stack *s, int v) { if (s->top == CAP) return false; s->data[s->top++] = v; return true; }
static bool pop(Stack *s, int *v) { if (s->top == 0) return false; *v = s->data[--s->top]; return true; }

int main(void)
{
    Stack s = {{0}, 0};
    int v;
    push(&s, 10); push(&s, 20);
    while (pop(&s, &v)) printf("%d ", v);
    putchar('\n');
    return 0;
}
