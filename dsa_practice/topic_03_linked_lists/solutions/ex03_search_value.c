/* Search a linked list for a target value. */
#include <stdbool.h>
#include <stdio.h>

typedef struct Node { int data; struct Node *next; } Node;

int main(void)
{
    Node c = {9, NULL}, b = {5, &c}, a = {2, &b};
    int target = 5;
    bool found = false;
    for (Node *p = &a; p != NULL; p = p->next) {
        if (p->data == target) found = true;
    }
    printf("found=%s\n", found ? "yes" : "no");
    return 0;
}
