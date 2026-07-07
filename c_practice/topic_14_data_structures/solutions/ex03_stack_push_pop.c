/*
 * ex03_stack_push_pop.c - Fixed-size LIFO stack.
 * Key concept: push/pop update one top index.
 */
#include <stdbool.h>
#include <stdio.h>

#define STACK_CAP 4U

typedef struct {
    int data[STACK_CAP];
    size_t top;
} Stack_t;

static bool push(Stack_t *s, int value)
{
    if (s->top >= STACK_CAP) {
        return false;
    }
    s->data[s->top++] = value;
    return true;
}

static bool pop(Stack_t *s, int *value)
{
    if (s->top == 0U) {
        return false;
    }
    *value = s->data[--s->top];
    return true;
}

int main(void)
{
    Stack_t stack = {{0}, 0U};
    int value;
    push(&stack, 10);
    push(&stack, 20);
    while (pop(&stack, &value)) {
        printf("%d\n", value);
    }
    return 0;
}
