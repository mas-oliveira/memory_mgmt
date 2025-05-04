#include "munit.h"
#include "exercise.h"

static MunitResult test_change_filetype_cpp_to_python(const MunitParameter params[], void* data) {
  codefile_t original;
  original.lines = 100;
  original.filetype = 1;
  codefile_t result = change_filetype(&original, 2);

  munit_assert_int(result.filetype, ==, 2);
  munit_assert_int(result.lines, ==, 100);

  return MUNIT_OK;
}

static MunitResult test_change_filetype_same_type(const MunitParameter params[], void* data) {
  codefile_t original;
  original.lines = 50;
  original.filetype = 3;
  codefile_t result = change_filetype(&original, 3);

  munit_assert_int(result.filetype, ==, 3);
  munit_assert_int(result.lines, ==, 50);

  return MUNIT_OK;
}

static MunitResult test_change_filetype_java_to_rust(const MunitParameter params[], void* data) {
  codefile_t original;
  original.lines = 200;
  original.filetype = 4;
  codefile_t result = change_filetype(&original, 5);

  munit_assert_int(result.filetype, ==, 5);
  munit_assert_int(result.lines, ==, 200);

  return MUNIT_OK;
}

static MunitResult test_change_filetype_zero_lines(const MunitParameter params[], void* data) {
  codefile_t original;
  original.lines = 0;
  original.filetype = 1;
  codefile_t result = change_filetype(&original, 6);

  munit_assert_int(result.filetype, ==, 6);
  munit_assert_int(result.lines, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_change_filetype_no_mutation(const MunitParameter params[], void* data) {
  codefile_t original;
  original.lines = 150;
  original.filetype = 7;
  codefile_t backup = original;
  codefile_t result = change_filetype(&original, 8);

  munit_assert_int(result.filetype, ==, 8);
  munit_assert_int(original.filetype, ==, backup.filetype);
  munit_assert_int(original.lines, ==, backup.lines);

  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_change_filetype_cpp_to_python", test_change_filetype_cpp_to_python, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_change_filetype_same_type", test_change_filetype_same_type, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_change_filetype_java_to_rust", test_change_filetype_java_to_rust, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_change_filetype_zero_lines", test_change_filetype_zero_lines, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_change_filetype_no_mutation", test_change_filetype_no_mutation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/change_filetype",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
