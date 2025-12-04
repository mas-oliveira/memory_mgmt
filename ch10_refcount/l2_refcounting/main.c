#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /int-refcount
   ---------------------------------------------------------- */
static MunitResult test_int_has_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_integer(10);

    munit_assert_not_null(obj);
    munit_assert_int(obj->refcount, ==, 1);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /float-refcount
   ---------------------------------------------------------- */
static MunitResult test_float_has_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(42.0);

    munit_assert_not_null(obj);
    munit_assert_int(obj->refcount, ==, 1);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    { "/int-refcount",   test_int_has_refcount,   NULL, NULL,
      MUNIT_TEST_OPTION_NONE, NULL },

    { "/float-refcount", test_float_has_refcount, NULL, NULL,
      MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* ----------------------------------------------------------
   Suite
   ---------------------------------------------------------- */
static const MunitSuite suite = {
    "/refcount",
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
