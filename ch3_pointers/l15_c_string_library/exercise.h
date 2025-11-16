#include <string.h>

#define MAX_BUF_SIZE 64
#define UNDEFINED_LEN -1
#define NULL_TERMINATOR_SIZE 1

typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src);
