#include <stdlib.h>
#include <string.h>

#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /copies_value
   ---------------------------------------------------------- */
static MunitResult test_str_copied(
    const MunitParameter params[], void *user_data)
{
    const char *input = "Hello, World!";
    snek_object_t *obj = new_snek_string(input);

    /* Deve ser STRING */
    munit_assert_int(obj->kind, ==, STRING);

    /* Deve ser uma cópia, não o mesmo ponteiro */
    munit_assert_ptr_not_equal(obj->data.v_string, input);

    /* Mas deve conter o mesmo texto */
    munit_assert_string_equal(obj->data.v_string, input);

    /* Libertar */
    free(obj->data.v_string);
    free(obj);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    {
        "/copies_value",
        test_str_copied,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* ----------------------------------------------------------
   Suite
   ---------------------------------------------------------- */
static const MunitSuite suite = {
    "/object_string",
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
