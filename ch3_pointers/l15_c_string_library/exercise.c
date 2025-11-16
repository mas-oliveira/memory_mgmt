#include <string.h>
#include "exercise.h"

int smart_append(TextBuffer* dest, const char* src) {
  int src_len;

  if (src == NULL)
    return 1;

  src_len = strlen(src);
  if (src_len <= 0)
    return 1;

  int space_left = MAX_BUF_SIZE - 1 - dest->length;

  if (src_len > space_left) {
    if (space_left > 0) {
      strncat(dest->buffer, src, space_left);
      dest->buffer[MAX_BUF_SIZE - 1] = '\0';
      dest->length = MAX_BUF_SIZE - 1;
    }
    return 1; 
  }

  strcat(dest->buffer, src);
  dest->length += src_len;
  return 0;
}
