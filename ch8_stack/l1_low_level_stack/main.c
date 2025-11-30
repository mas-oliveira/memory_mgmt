#include "munit.h"
#include "snekstack.h"
#include <stdlib.h>

/* --------------------------------------------------------- */
/* create_stack_small                                        */
/* --------------------------------------------------------- */
static MunitResult create_stack_small(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(3);

    munit_assert_int(s->capacity, ==, 3);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* create_stack_large                                        */
/* --------------------------------------------------------- */
static MunitResult create_stack_large(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(100);

    munit_assert_int(s->capacity, ==, 100);
    munit_assert_int(s->count, ==, 0);
    munit_assert_ptr_not_null(s->data);

    free(s->data);
    free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* Test list                                                 */
/* --------------------------------------------------------- */
static MunitTest tests[] = {
    {
        "/create_stack_small",
        create_stack_small,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/create_stack_large",
        create_stack_large,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
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
