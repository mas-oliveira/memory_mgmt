#include "munit.h"
#include "coord.h"

static MunitResult test_new_coordinate1(const MunitParameter params[], void* data) {
  struct Coordinate c = {1, 2, 3};
  munit_assert_int(c.x, ==, 1);
  munit_assert_int(c.y, ==, 2);
  munit_assert_int(c.z, ==, 3);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/create_coordinate1", test_new_coordinate1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/coordinates",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}