#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "vm.h"

/* ---------- TEST 1: single frame ---------- */
static MunitResult test_single_frame(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    frame_t *frame = vm_new_frame(vm);
    munit_assert_not_null(frame);

    snek_object_t *teej_skill = new_snek_integer(vm, 420);
    snek_object_t *lane_skill = new_snek_string(vm, "issues");

    /* First mark: nothing referenced => nothing marked */
    mark(vm);
    munit_assert_false(teej_skill->is_marked);
    munit_assert_false(lane_skill->is_marked);

    /* Add references to the frame */
    frame_reference_object(frame, teej_skill);
    frame_reference_object(frame, lane_skill);

    /* Now marking should mark both */
    mark(vm);
    munit_assert_true(teej_skill->is_marked);
    munit_assert_true(lane_skill->is_marked);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- TEST 2: multi-frame ---------- */
static MunitResult test_multi_frame(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    frame_t *frame  = vm_new_frame(vm);
    frame_t *frame2 = vm_new_frame(vm);

    snek_object_t *teej_skill  = new_snek_integer(vm, 420);
    snek_object_t *lane_skill  = new_snek_string(vm, "issues");
    snek_object_t *prime_skill = new_snek_string(vm, "infinite");

    frame_reference_object(frame,  teej_skill);
    frame_reference_object(frame,  lane_skill);
    frame_reference_object(frame2, prime_skill);

    mark(vm);

    munit_assert_true(teej_skill->is_marked);
    munit_assert_true(lane_skill->is_marked);
    munit_assert_true(prime_skill->is_marked);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- SUITE ---------- */

static MunitTest tests[] = {
    { "/test_single_frame", test_single_frame, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_multi_frame",  test_multi_frame,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
