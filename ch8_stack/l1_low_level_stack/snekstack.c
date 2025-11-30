#include "snekstack.h"
#include <stdlib.h>

snek_stack_t *stack_new(size_t capacity) {
    snek_stack_t *Stack = (snek_stack_t *)malloc(sizeof(snek_stack_t));
    if (Stack == NULL) {
        return NULL;
    }

    Stack -> count = 0;
    Stack -> capacity = capacity;

    Stack -> data = malloc(capacity * sizeof(void *));
    if (Stack -> data == NULL) {
        free(Stack);
        return NULL;
    }
    return Stack;
}
