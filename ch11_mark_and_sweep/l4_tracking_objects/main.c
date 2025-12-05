#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "snekobject.h"
#include "vm.h"

/* ---------- TEST 1 ---------- */
static MunitResult test_new_object(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    snek_object_t *obj = new_snek_integer(vm, 5);
    munit_assert_not_null(obj);

    /* kind must be INTEGER */
    munit_assert_int(obj->kind, ==, INTEGER);

    /* object must be tracked in vm->objects */
    munit_assert_ptr_equal(vm->objects->data[0], obj);

    /* free object manually if vm_free doesn't do that */
    free(obj);
    vm_free(vm);

    return MUNIT_OK;
}

/* ---------- TEST 2 ---------- */
static MunitResult test_vm_new(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    munit_assert_not_null(vm->frames);
    munit_assert_not_null(vm->objects);

    vm_free(vm);

    return MUNIT_OK;
}

/* ---------- TEST 3 ---------- */
static MunitResult test_frames_are_freed(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    vm_new_frame(vm);

    vm_free(vm);

    /* Não temos bootlib, logo só verificamos que não crashou */

    return MUNIT_OK;
}

/* ---------- TEST SUITE ---------- */

static MunitTest tests[] = {
    { "/test_vm_new", test_vm_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_frames_are_freed", test_frames_are_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_new_object", test_new_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
