#include "snekstack.h"
#include "stdlib.h"

void scary_double_push(snek_stack_t *s) {
    stack_push(s, (void *)1337);
    int *new_int = (int *)malloc(sizeof(int));
    *new_int = 1024;
    stack_push(s, new_int);
}
