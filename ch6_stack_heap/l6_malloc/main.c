#include "munit.h"
#include "exercise.h"
#include <stdlib.h>

static MunitResult test_allocate_scalar_array_size(const MunitParameter params[], void* data) {
  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);

  munit_assert_not_null(result);

  free(result);
  return MUNIT_OK;
}

static MunitResult test_allocate_scalar_array_values(const MunitParameter params[], void* data) {
  int size = 5;
  int multiplier = 2;
  int *result = allocate_scalar_array(size, multiplier);

  int expected[5] = {0, 2, 4, 6, 8};

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, expected[i]);
  }

  free(result);
  return MUNIT_OK;
}

static MunitResult test_allocate_scalar_array_zero_multiplier(const MunitParameter params[], void* data) {
  int size = 3;
  int multiplier = 0;
  int *result = allocate_scalar_array(size, multiplier);

  for (int i = 0; i < size; i++) {
    munit_assert_int(result[i], ==, 0);
  }

  free(result);
  return MUNIT_OK;
}

static MunitResult test_allocate_too_much(const MunitParameter params[], void* data) {
  int size = 1024 * 1024 * 100;
  int multiplier = 1;
  int *result = allocate_scalar_array(size, multiplier);

  munit_assert_null(result);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  {
    "/test_allocate_scalar_array_size",
    test_allocate_scalar_array_size,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    "/test_allocate_scalar_array_values",
    test_allocate_scalar_array_values,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    "/test_allocate_scalar_array_zero_multiplier",
    test_allocate_scalar_array_zero_multiplier,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  {
    "/test_allocate_too_much",
    test_allocate_too_much,
    NULL, NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/allocate_scalar_array",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
