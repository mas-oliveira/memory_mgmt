#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "vm.h"

/* ---------- TEST 1 ---------- */
static MunitResult test_field_exists(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    snek_object_t *lane_courses = new_snek_integer(vm, 20);
    snek_object_t *teej_courses = new_snek_integer(vm, 1);

    /* Just accessing the field to ensure it exists */
    (void)lane_courses->is_marked;
    (void)teej_courses->is_marked;

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- TEST 2 ---------- */
static MunitResult test_marked_is_false(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();

    snek_object_t *lane_courses = new_snek_integer(vm, 20);
    snek_object_t *teej_courses = new_snek_integer(vm, 1);

    munit_assert_false(lane_courses->is_marked);
    munit_assert_false(teej_courses->is_marked);

    vm_free(vm);
    return MUNIT_OK;
}

/* ---------- SUITE ---------- */

static MunitTest tests[] = {
    { "/test_field_exists",     test_field_exists,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_marked_is_false",  test_marked_is_false,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
