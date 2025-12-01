#include "munit.h"
#include "snekstack.h"
#include "exercise.h"   // onde está declarada stack_push_multiple_types
#include <stdlib.h>

/* --------------------------------------------------------- */
/* multiple_types_stack                                      */
/* --------------------------------------------------------- */
static MunitResult multiple_types_stack(
    const MunitParameter params[], void *user_data) {

    snek_stack_t *s = stack_new(4);
    munit_assert_ptr_not_null(s);

    stack_push_multiple_types(s);
    munit_assert_int(s->count, ==, 2);

    // Primeiro item é um float*
    float *f = s->data[0];
    munit_assert_double(*f, ==, 3.14);

    // Segundo item é um char*
    char *string = s->data[1];
    munit_assert_string_equal(string, "Sneklang is blazingly slow!");

    free(f);
    free(string);
    stack_free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* Lista de testes                                           */
/* --------------------------------------------------------- */
static MunitTest tests[] = {
    {
        "/multiple_types_stack",
        multiple_types_stack,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* --------------------------------------------------------- */
/* Suite                                                     */
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
