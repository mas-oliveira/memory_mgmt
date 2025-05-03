#include "munit.h"
#include "my_array_struct.h"

static MunitResult test_array_example(const MunitParameter params[], void* data) {
  struct MyArrayStruct arr = {{1, 2, 3}, 3};
  munit_assert_int(arr.values[0], ==, 1);
  munit_assert_int(arr.values[1], ==, 2);
  munit_assert_int(arr.count, ==, 3);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/array_test", test_array_example, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/struct_array",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}