#include "munit.h"
#include "exercise.h"
#include <string.h>

static MunitResult test_return_1_for_null_value(const MunitParameter params[], void* data) {
  TextBuffer dest;
  const char* src = NULL;
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);
  return MUNIT_OK;
}

static MunitResult test_smart_append_empty_buffer(const MunitParameter params[], void* data) {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;
  const char* src = "Hello";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 0);
  munit_assert_string_equal(dest.buffer, "Hello");
  munit_assert_int(dest.length, ==, 5);
  return MUNIT_OK;
}

static MunitResult test_smart_append_full_buffer(const MunitParameter params[], void* data) {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a very long string that will fill up the entire buffer.");
  dest.length = 63;
  const char* src = " Extra";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);
  munit_assert_string_equal(dest.buffer, "This is a very long string that will fill up the entire buffer.");
  munit_assert_int(dest.length, ==, 63);
  return MUNIT_OK;
}

static MunitResult test_smart_append_overflow(const MunitParameter params[], void* data) {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a long string");
  dest.length = 21;
  const char* src = " that will fill the whole buffer and leave no space for some of the chars.";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1);
  munit_assert_string_equal(dest.buffer, "This is a long string that will fill the whole buffer and leave");
  munit_assert_int(dest.length, ==, 63);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_return_1_for_null_value", test_return_1_for_null_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_smart_append_empty_buffer", test_smart_append_empty_buffer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_smart_append_full_buffer", test_smart_append_full_buffer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_smart_append_overflow", test_smart_append_overflow, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/smart_append",  // Suite name
  tests,            // Tests
  NULL,             // No nested suites
  1,                // Number of iterations
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
