#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "vm.h"

/* ---------- TEST 1 ---------- */
static MunitResult test_one_ref(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    frame_t *frame = vm_new_frame(vm);
    munit_assert_not_null(frame);

    snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
    munit_assert_not_null(lanes_wpm);

    frame_reference_object(frame, lanes_wpm);

    munit_assert_int(frame->references->count, ==, 1);
    munit_assert_ptr_equal(frame->references->data[0], lanes_wpm);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- TEST 2 ---------- */
static MunitResult test_multi_ref(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    frame_t *frame = vm_new_frame(vm);
    munit_assert_not_null(frame);

    snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
    snek_object_t *teej_wpm  = new_snek_integer(vm, 160);

    munit_assert_not_null(lanes_wpm);
    munit_assert_not_null(teej_wpm);

    frame_reference_object(frame, lanes_wpm);
    frame_reference_object(frame, teej_wpm);

    munit_assert_int(frame->references->count, ==, 2);
    munit_assert_ptr_equal(frame->references->data[0], lanes_wpm);
    munit_assert_ptr_equal(frame->references->data[1], teej_wpm);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- SUITE ---------- */

static MunitTest tests[] = {
    { "/test_one_ref",  test_one_ref,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_multi_ref", test_multi_ref, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/mark-and-sweep",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
