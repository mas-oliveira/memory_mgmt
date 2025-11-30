#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void stack_push(snek_stack_t *stack, void *obj) {
    if (stack -> count == stack -> capacity) {
        stack -> data = realloc(stack -> data, 2 * stack -> capacity * sizeof(void *));
        stack -> capacity *= 2;
        if (stack -> data == NULL) {
            return;
        }
    }

    stack -> data[stack -> count] = obj;

    stack -> count++;
}

snek_stack_t *stack_new(size_t capacity) {
    snek_stack_t *stack = (snek_stack_t *)malloc(sizeof(snek_stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack -> count = 0;
    stack -> capacity = capacity;

    stack -> data = malloc(capacity * sizeof(void *));
    if (stack -> data == NULL) {
        free(stack);
        return NULL;
    }
    return stack;
}
