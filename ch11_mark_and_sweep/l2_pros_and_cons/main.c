#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "vm.h"
#include "bootlib.h"

// ----------------------------
// Test: vm_new initializes fields correctly
// ----------------------------
static MunitResult
test_vm_new(const MunitParameter params[], void *data) {
  (void) params;
  (void) data;

  vm_t *vm = vm_new();

  munit_assert_int(vm->frames->capacity, ==, 8);
  munit_assert_int(vm->objects->capacity, ==, 8);

  vm_free(vm);
  return MUNIT_OK;
}

// ----------------------------
// Test: vm_new followed by vm_free frees everything
// ----------------------------
static MunitResult
test_vm_new_free(const MunitParameter params[], void *data) {
  (void) params;
  (void) data;

  vm_t *vm = vm_new();
  vm_free(vm);

  munit_assert(boot_all_freed());

  return MUNIT_OK;
}

// ----------------------------
// Test Table
// ----------------------------
static MunitTest tests[] = {
    {
        "/vm/test_vm_new",
        test_vm_new,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/vm/test_vm_new_free",
        test_vm_new_free,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// ----------------------------
// Test Suite
// ----------------------------
static const MunitSuite suite = {
    "/mark-and-sweep", // Suite name
    tests,             // Tests
    NULL,              // Suites
    1,                 // iterations
    MUNIT_SUITE_OPTION_NONE
};

// ----------------------------
// Main
// ----------------------------
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
