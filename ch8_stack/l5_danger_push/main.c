#include "munit.h"
#include <stdlib.h>
#include "exercise.h"  // onde a função scary_double_push está declarada

/* --------------------------------------------------------- */
/* heterogenous_stack                                        */
/* --------------------------------------------------------- */
static MunitResult heterogenous_stack(
    const MunitParameter params[], void *data) {

    snek_stack_t *s = stack_new(2);
    munit_assert_ptr_not_null(s);

    scary_double_push(s);

    munit_assert_int(s->count, ==, 2);

    // Primeiro item: inteiro armazenado como ponteiro
    int value = (int)(intptr_t)s->data[0]; // cast seguro de ponteiro -> int
    munit_assert_int(value, ==, 1337);

    // Segundo item: ponteiro para inteiro
    int *pointer = s->data[1];
    munit_assert_int(*pointer, ==, 1024);

    free(pointer);
    stack_free(s);

    return MUNIT_OK;
}

/* --------------------------------------------------------- */
/* Test list                                                 */
/* --------------------------------------------------------- */
static MunitTest tests[] = {
    { "/heterogenous_stack", heterogenous_stack, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
