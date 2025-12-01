#include <stdio.h>
#include "snekstack.h"
#include "stdlib.h"
#include <string.h>

#define MAX_CAPACITY 100

void stack_push_multiple_types(snek_stack_t *s) {
    float *pi_pointer = (float *)malloc(sizeof(float));
    if (pi_pointer == NULL) {
        return;
    }
    *pi_pointer = 3.14;
    stack_push(s, pi_pointer);

    char *sentence_pointer = (char *)malloc(MAX_CAPACITY * sizeof(char));
    if(sentence_pointer == NULL) {
        return;
    }
    strcpy(sentence_pointer, "Sneklang is blazingly slow!");

    stack_push(s, sentence_pointer);
}


void scary_double_push(snek_stack_t *s) {
    stack_push(s, (void *)1337);
    int *new_int = (int *)malloc(sizeof(int));
    *new_int = 1024;
    stack_push(s, new_int);
}
