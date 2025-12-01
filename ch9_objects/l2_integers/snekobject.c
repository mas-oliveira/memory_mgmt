#include <stdlib.h>

#include "snekobject.h"

snek_object_t *new_snek_integer(int value) {
  snek_object_t *new_snek_object = (snek_object_t *)malloc(sizeof(snek_object_t));
  if (new_snek_object == NULL) {
    return NULL;
  }

  new_snek_object -> kind = INTEGER;
  new_snek_object -> data.v_int = value;

  return new_snek_object;
}
