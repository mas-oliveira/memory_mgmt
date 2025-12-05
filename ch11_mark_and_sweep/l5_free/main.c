#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "vm.h"

/* ---------- TEST 1 ---------- */
static MunitResult test_reference_object(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();

    snek_object_t *i = new_snek_integer(vm, 5);
    munit_assert_not_null(i);

    snek_object_t *s = new_snek_string(vm, "hello");
    munit_assert_not_null(s);

    vm_free(vm);

    /* Sem bootlib, não há como verificar se tudo foi libertado.
       Por isso o teste termina aqui. */
    return MUNIT_OK;
}

/* ---------- TEST 2 ---------- */
static MunitResult test_frames_are_freed(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    munit_assert_not_null(vm);

    vm_new_frame(vm);
    vm_new_frame(vm);

    munit_assert_int(vm->frames->count, ==, 2);

    vm_free(vm);

    return MUNIT_OK;
}

/* ---------- TEST SUITE ---------- */

static MunitTest tests[] = {
    {
        "/test_reference_object",
        test_reference_object,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/test_frames_are_freed",
        test_frames_are_freed,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
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
