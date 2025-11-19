#include <stdio.h>

typedef enum {
  BIG = 123412341234,
  BIGGER,
  BIGGEST,
} BigNumbers;

typedef enum {
  HTTP_BAD_REQUEST = 400,
  HTTP_UNAUTHORIZED = 401,
  HTTP_NOT_FOUND = 404,
  HTTP_I_AM_A_TEAPOT = 418,
  HTTP_INTERNAL_SERVER_ERROR = 500
} HttpErrorCode;

typedef enum { // se mudar o first para -1 deixa de caber em 4 bytes, isto porque ultrapassa o range de unsigned int entao passa a ser 8
  First = 0,
  Last = 4294967293
} NumberStudent;

int main() {
  printf("The size of BigNumbers is %zu bytes\n", sizeof(BigNumbers));
  printf("The size of HttpErrorCode is %zu bytes\n", sizeof(HttpErrorCode));
  printf("The size of NumberStudent is %zu bytes\n", sizeof(NumberStudent));
  return 0;
}
