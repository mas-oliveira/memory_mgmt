#include <stdlib.h>
#include <string.h>

void swap(void *vp1, void *vp2, size_t size) {
  void *tmp_buffer = malloc(size);
  if (tmp_buffer == NULL) {
    return;
  }
  memcpy(tmp_buffer, vp1, size);
  memcpy(vp1, vp2, size);
  memcpy(vp2, tmp_buffer, size);
  free(tmp_buffer);
}
