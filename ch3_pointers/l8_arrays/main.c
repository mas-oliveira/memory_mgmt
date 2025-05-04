#include "munit.h"
#include "exercise.h"

static MunitResult test_update_file_basic(const MunitParameter params[], void* data) {
  int filedata[200] = {0};
  update_file(filedata, 1, 100);

  munit_assert_int(filedata[1], ==, 100);
  munit_assert_int(filedata[2], ==, 1);
  munit_assert_int(filedata[199], ==, 0);

  return MUNIT_OK;
}

static MunitResult test_update_file_different_values(const MunitParameter params[], void* data) {
  int filedata[200];
  for (int i = 0; i < 200; i++) {
    filedata[i] = 69;
  }

  update_file(filedata, 3, 250);

  munit_assert_int(filedata[1], ==, 250);
  munit_assert_int(filedata[2], ==, 3);
  munit_assert_int(filedata[199], ==, 0);

  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/test_update_file_basic", test_update_file_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_update_file_different_values", test_update_file_different_values, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/update_file",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
