#include "munit.h"
#include "exercise.h"
#include <string.h>

static MunitResult test_concat_empty_strings(const MunitParameter params[], void* data) {
  char str1[100] = "";
  const char *str2 = "";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "");
  return MUNIT_OK;
}

static MunitResult test_concat_empty_to_nonempty(const MunitParameter params[], void* data) {
  char str1[100] = "Hello";
  const char *str2 = "";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "Hello");
  return MUNIT_OK;
}

static MunitResult test_concat_small_strings(const MunitParameter params[], void* data) {
  char str1[100] = "Hello ";
  const char *str2 = "World";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "Hello World");
  return MUNIT_OK;
}

static MunitResult test_concat_long_strings(const MunitParameter params[], void* data) {
  char str1[200] = "This is a longer string that ";
  const char *str2 = "will be concatenated with another long string.";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "This is a longer string that will be concatenated with another long string.");
  return MUNIT_OK;
}

static MunitResult test_concat_nonempty_to_empty(const MunitParameter params[], void* data) {
  char str1[100] = "";
  const char *str2 = "Hello";
  concat_strings(str1, str2);
  munit_assert_string_equal(str1, "Hello");
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_concat_empty_strings", test_concat_empty_strings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_concat_empty_to_nonempty", test_concat_empty_to_nonempty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_concat_small_strings", test_concat_small_strings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_concat_long_strings", test_concat_long_strings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_concat_nonempty_to_empty", test_concat_nonempty_to_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/concat_strings",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
