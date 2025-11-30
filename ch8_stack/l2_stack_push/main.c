#include "munit.h"
#include "snekstack.h"
#include <stdlib.h>

/* --------------------------------------------------------- */
/* create_stack                                             */
/* --------------------------------------------------------- */
static MunitResult create_stack(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(10);

    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 10);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* push_stack                                               */
/* --------------------------------------------------------- */
static MunitResult push_stack(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(2);

    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 2);
    munit_assert_ptr_equal(s->data[0], &a);

    free(s->data);
    free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* push_double_capacity                                     */
/* --------------------------------------------------------- */
static MunitResult push_double_capacity(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(2);

    munit_assert_ptr_not_null(s);
    munit_assert_int(s->capacity, ==, 2);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    // Força realloc
    stack_push(s, &a);

    munit_assert_int(s->capacity, ==, 4);
    munit_assert_int(s->count, ==, 3);

    free(s->data);
    free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* Test list                                                 */
/* --------------------------------------------------------- */
static MunitTest tests[] = {
    { "/create_stack", create_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_stack", push_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/push_double_capacity", push_double_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* --------------------------------------------------------- */
/* Test suite                                                */
/* --------------------------------------------------------- */
static const MunitSuite suite = {
    "/snekstack",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

/* --------------------------------------------------------- */
/* main                                                      */
/* --------------------------------------------------------- */
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
