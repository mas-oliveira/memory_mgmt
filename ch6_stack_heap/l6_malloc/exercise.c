#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"

int *allocate_scalar_array(int size, int multiplier) {
  int *ptr, *ret_ptr;

  ptr = (int*) malloc(size * sizeof(int));
  
  if (ptr == NULL) {
    fprintf(stderr, "Memory allocation for ptr failed.\n");
    return NULL;
  }

  ret_ptr = ptr;

  for (int i = 0; i < size; i++) {
    *ptr = i * multiplier;
    ptr ++;
  }

  return ret_ptr;
}
