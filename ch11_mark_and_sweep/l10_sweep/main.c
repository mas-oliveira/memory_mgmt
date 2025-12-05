#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "sneknew.h"
#include "snekobject.h"
#include "vm.h"

/* -----------------------------------------
   TEST 1: SIMPLE MARK-AND-SWEEP
   ----------------------------------------- */

static MunitResult test_simple(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);

    snek_object_t *s = new_snek_string(vm, "I wish I knew how to read.");
    frame_reference_object(f1, s);

    /* GC should NOT free s because f1 still exists */
    vm_collect_garbage(vm);
    munit_assert_int(vm->objects->count, ==, 1);

    /* Now delete the frame => object becomes unreachable */
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);

    /* Now the string should be gone */
    munit_assert_int(vm->objects->count, ==, 0);

    vm_free(vm);

    return MUNIT_OK;
}

/* -----------------------------------------
   TEST 2: FULL MARK-AND-SWEEP
   ----------------------------------------- */

static MunitResult test_full(const MunitParameter params[], void *user_data) {
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);
    frame_t *f2 = vm_new_frame(vm);
    frame_t *f3 = vm_new_frame(vm);

    snek_object_t *s1 = new_snek_string(vm, "This string is going into frame 1");
    frame_reference_object(f1, s1);

    snek_object_t *s2 = new_snek_string(vm, "This string is going into frame 2");
    frame_reference_object(f2, s2);

    snek_object_t *s3 = new_snek_string(vm, "This string is going into frame 3");
    frame_reference_object(f3, s3);

    snek_object_t *i1 = new_snek_integer(vm, 69);
    snek_object_t *i2 = new_snek_integer(vm, 420);
    snek_object_t *i3 = new_snek_integer(vm, 1337);

    snek_object_t *v = new_snek_vector3(vm, i1, i2, i3);

    frame_reference_object(f2, v);
    frame_reference_object(f3, v);

    /* We should have exactly 7 objects alive */
    munit_assert_int(vm->objects->count, ==, 7);

    /* Remove top frame → s3 becomes unreachable */
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);

    /* Now 6 objects remain (everything except s3) */
    munit_assert_int(vm->objects->count, ==, 6);

    /* Remove remaining frames */
    frame_free(vm_frame_pop(vm)); /* f2 */
    frame_free(vm_frame_pop(vm)); /* f1 */
    vm_collect_garbage(vm);

    /* All objects should now be collected */
    munit_assert_int(vm->objects->count, ==, 0);

    vm_free(vm);

    return MUNIT_OK;
}

/* -----------------------------------------
   MUNIT SUITE
   ----------------------------------------- */

static MunitTest tests[] = {
    { "/test_simple", test_simple, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_full",   test_full,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
