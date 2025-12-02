#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /empty
   ---------------------------------------------------------- */
static MunitResult test_create_empty_array(
    const MunitParameter params[], void *data)
{
    snek_object_t *obj = new_snek_array(2);
    munit_assert_ptr_not_null(obj);

    munit_assert_int(obj->kind, ==, ARRAY);
    munit_assert_int(obj->data.v_array.size, ==, 2);

    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /calloc
   ---------------------------------------------------------- */
static MunitResult test_used_calloc(
    const MunitParameter params[], void *data)
{
    snek_object_t *obj = new_snek_array(2);
    munit_assert_ptr_not_null(obj);

    /* calloc deve garantir que cada elemento é NULL */
    munit_assert_ptr_null(obj->data.v_array.elements[0]);
    munit_assert_ptr_null(obj->data.v_array.elements[1]);

    free(obj->data.v_array.elements);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    { "/empty",  test_create_empty_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/calloc", test_used_calloc,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
