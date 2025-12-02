#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /set_and_get
   ---------------------------------------------------------- */
static MunitResult
test_array(const MunitParameter params[], void *user_data) {

    /* Create an array */
    snek_object_t *obj = new_snek_array(2);

    /* Create objects */
    snek_object_t *first = new_snek_string("First");
    snek_object_t *second = new_snek_integer(3);

    munit_assert_true(snek_array_set(obj, 0, first));
    munit_assert_true(snek_array_set(obj, 1, second));

    snek_object_t *retrieved_first = snek_array_get(obj, 0);
    munit_assert_not_null(retrieved_first);
    munit_assert_int(retrieved_first->kind, ==, STRING);
    munit_assert_ptr_equal(first, retrieved_first);

    snek_object_t *retrieved_second = snek_array_get(obj, 1);
    munit_assert_not_null(retrieved_second);
    munit_assert_int(retrieved_second->kind, ==, INTEGER);
    munit_assert_ptr_equal(second, retrieved_second);

    /* Manual frees */
    free(first->data.v_string);
    free(first);
    free(second);
    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /set_outside
   ---------------------------------------------------------- */
static MunitResult
test_set_outside_bounds(const MunitParameter params[], void *user_data) {

    snek_object_t *obj = new_snek_array(2);
    snek_object_t *outside = new_snek_string("First");

    munit_assert_true(snek_array_set(obj, 1, outside));
    munit_assert_false(snek_array_set(obj, 100, outside));

    free(outside->data.v_string);
    free(outside);
    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /get_outside
   ---------------------------------------------------------- */
static MunitResult
test_get_outside_bounds(const MunitParameter params[], void *user_data) {

    snek_object_t *obj = new_snek_array(1);
    snek_object_t *first = new_snek_string("First");

    munit_assert_true(snek_array_set(obj, 0, first));

    munit_assert_null(snek_array_get(obj, 1));

    free(first->data.v_string);
    free(first);
    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Test list
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    {
        "/set_and_get",
        test_array,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/set_outside",
        test_set_outside_bounds,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/get_outside",
        test_get_outside_bounds,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* ----------------------------------------------------------
   Suite
   ---------------------------------------------------------- */
static const MunitSuite suite = {
    "/object-array",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

/* ----------------------------------------------------------
   main
   ---------------------------------------------------------- */
int main(int argc, char *argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
