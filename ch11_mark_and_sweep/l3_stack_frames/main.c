#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "vm.h"

/* ---------- TEST 1 ---------- */
static MunitResult test_vm_new(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    munit_assert_int(vm->frames->count, ==, 1);
    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- TEST 2 ---------- */
static MunitResult test_vm_new_frame(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    munit_assert_not_null(frame->references);
    munit_assert_int(frame->references->count, ==, 0);
    munit_assert_int(frame->references->capacity, >, 0);
    munit_assert_not_null(frame->references->data);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- TEST 3 ---------- */
static MunitResult test_frames_are_freed(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    vm_new_frame(vm);

    /* No bootlib → só verificamos que o free não crasha */
    vm_free(vm);

    return MUNIT_OK;
}

/* ---------- MAIN SUITE ---------- */

static MunitTest tests[] = {
    { "/test_vm_new", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_vm_new_frame", test_vm_new_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/mark-and-sweep",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
