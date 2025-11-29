#include "stdlib.h"

#include "exercise.h"

void allocate_int(int **pointer_pointer, int value) {
    int *int_ptr = (int *)malloc(sizeof(int));
    if (int_ptr == NULL) {
        fprintf(stderr, "Error allocating memory for int_ptr\n");
        return;
    }

    *pointer_pointer = int_ptr;
    
    *int_ptr = value;
}
