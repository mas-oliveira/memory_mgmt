#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /integer_constant
   ---------------------------------------------------------- */
static MunitResult test_integer_constant(
    const MunitParameter params[], void *data)
{
    munit_assert_int(INTEGER, ==, 0);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /integer_obj
   ---------------------------------------------------------- */
static MunitResult test_integer_obj(
    const MunitParameter params[], void *data)
{
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    munit_assert_ptr_not_null(obj);

    obj->kind = INTEGER;
    obj->data.v_int = 0;

    munit_assert_int(obj->kind, ==, INTEGER);
    munit_assert_int(obj->data.v_int, ==, 0);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    {
        "/integer_constant",
        test_integer_constant,
        NULL, NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/integer_obj",
        test_integer_obj,
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
    "/object_integer_def",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

/* ----------------------------------------------------------
   main
   ---------------------------------------------------------- */
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
