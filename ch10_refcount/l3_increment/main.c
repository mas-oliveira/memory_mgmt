#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /inc-refcount
   ---------------------------------------------------------- */
static MunitResult test_inc_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_integer(10);
    munit_assert_not_null(obj);

    munit_assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /inc-refcount-more
   ---------------------------------------------------------- */
static MunitResult test_inc_refcount_more(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);
    munit_assert_not_null(obj);

    munit_assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);

    munit_assert_int(obj->refcount, ==, 6);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /null-object
   ---------------------------------------------------------- */
static MunitResult test_null_obj(const MunitParameter params[], void *data) {
    /* Deve simplesmente não crashar */
    refcount_inc(NULL);

    /* O teste só confirma que chegámos aqui */
    munit_assert_int(1, ==, 1);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    { "/inc-refcount",       test_inc_refcount,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inc-refcount-more",  test_inc_refcount_more,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null-object",        test_null_obj,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
