#include "munit.h"
#include "snek.h"

static MunitResult size_of_addr_16(const MunitParameter params[], void* data) {
  unsigned long size = size_of_addr(16);
  munit_assert_ulong(size, ==, 8);
  return MUNIT_OK;
}

static MunitResult size_of_addr_32(const MunitParameter params[], void* data) {
  unsigned long size = size_of_addr(32);
  munit_assert_ulong(size, ==, 8);
  return MUNIT_OK;
}

static MunitResult size_of_addr_64(const MunitParameter params[], void* data) {
  unsigned long size = size_of_addr(64);
  munit_assert_ulong(size, ==, 8);
  return MUNIT_OK;
}

static MunitResult size_of_addr_128(const MunitParameter params[], void* data) {
  unsigned long size = size_of_addr(128);
  munit_assert_ulong(size, ==, 8);
  return MUNIT_OK;
}

static MunitTest tests[] = {
  { "/size_of_addr_16", size_of_addr_16, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/size_of_addr_32", size_of_addr_32, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/size_of_addr_64", size_of_addr_64, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/size_of_addr_128", size_of_addr_128, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/colors",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
