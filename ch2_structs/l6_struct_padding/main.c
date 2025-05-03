#include "munit.h"
#include "exercise.h"

static MunitResult test_optimal_size(const MunitParameter params[], void* data) {
  munit_assert_int(sizeof(sneklang_var_t), ==, 24);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_optimal_size", test_optimal_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/padding",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
