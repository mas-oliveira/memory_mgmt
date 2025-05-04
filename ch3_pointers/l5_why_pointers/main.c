#include "munit.h"
#include "coordinate.h"

coordinate_t new_coordinate(int x, int y, int z) {
  return (coordinate_t){.x = x, .y = y, .z = z};
}

static MunitResult test_unchanged(const MunitParameter params[], void* data) {
  coordinate_t old = new_coordinate(1, 2, 3);
  munit_assert_int(old.x, ==, 1);

  coordinate_update_x(old, 4);
  munit_assert_int(old.x, ==, 1);

  return MUNIT_OK;
}

static MunitResult test_changed(const MunitParameter params[], void* data) {
  coordinate_t old = new_coordinate(1, 2, 3);
  munit_assert_int(old.x, ==, 1);

  coordinate_t new = coordinate_update_and_return_x(old, 4);
  munit_assert_int(new.x, ==, 4);
  munit_assert_int(old.x, ==, 1);

  munit_assert_ptr_not_equal(&old, &new);

  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_unchanged", test_unchanged, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_changed", test_changed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/pointers",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
