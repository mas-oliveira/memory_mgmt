#include "munit.h"
#include "coord.h"

static MunitResult test_new_coordinate(const MunitParameter params[], void* data) {
  struct Coordinate c;
  c.x = 1;
  c.y = 2;
  c.z = 3;

  munit_assert_int(c.x, ==, 1);
  munit_assert_int(c.y, ==, 2);
  munit_assert_int(c.z, ==, 3);

  return MUNIT_OK;
}

static MunitResult test_scale_coordinate1(const MunitParameter params[], void* data) {
  struct Coordinate c = new_coord(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(c, 2);

  munit_assert_int(scaled.x, ==, 2);
  munit_assert_int(scaled.y, ==, 4);
  munit_assert_int(scaled.z, ==, 6);

  return MUNIT_OK;
}

static MunitResult test_scale_coordinate2(const MunitParameter params[], void* data) {
  struct Coordinate c = new_coord(4, 2, 0);
  struct Coordinate scaled = scale_coordinate(c, 2);

  munit_assert_int(scaled.x, ==, 8);
  munit_assert_int(scaled.y, ==, 4);
  munit_assert_int(scaled.z, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_original_unchanged(const MunitParameter params[], void* data) {
  struct Coordinate c = new_coord(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(c, 2);

  munit_assert_int(c.x, ==, 1);
  munit_assert_int(c.y, ==, 2);
  munit_assert_int(c.z, ==, 3);

  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/create_coordinate", test_new_coordinate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_scale_coordinate1", test_scale_coordinate1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_scale_coordinate2", test_scale_coordinate2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_original_unchanged", test_original_unchanged, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
