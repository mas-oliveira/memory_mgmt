#include "exercise.h"

void snek_zero_out(void *ptr, snek_object_kind_t kind){
  if(kind == INTEGER) {
    ptr = (snek_int_t *) ptr;
    ((snek_int_t *) ptr)->value = 0;
  }
  else if(kind == FLOAT) {
    ptr = (snek_float_t *) ptr;
    ((snek_float_t *) ptr)->value = 0.0;
  }  
  else if(kind == BOOL) {
    ptr = (snek_bool_t *) ptr;
    ((snek_bool_t *) ptr)->value = 0;
  }
}
