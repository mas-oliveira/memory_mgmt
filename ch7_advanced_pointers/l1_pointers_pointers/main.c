#include <stdlib.h>

#include "exercise.h"
#include "munit.h"

static MunitResult test_allocate(const MunitParameter params[], void* data) {
  int *pointer = NULL;
  allocate_int(&pointer, 10);

  munit_assert_not_null(pointer);
  munit_assert_int(*pointer, ==, 10);

  free(pointer);
  return MUNIT_OK;
}

static MunitResult test_does_not_overwrite(const MunitParameter params[], void* data) {
  int value = 5;
  int *pointer = &value;

  allocate_int(&pointer, 20);

  /* original value must remain unchanged */
  munit_assert_int(value, ==, 5);

  /* pointer must now point to a new allocated value */
  munit_assert_not_null(pointer);
  munit_assert_int(*pointer, ==, 20);

  free(pointer);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  {
    "/create",
    test_allocate,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    "/overwrite",
    test_does_not_overwrite,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/allocate_list",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
