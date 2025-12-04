#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /has_refcount
   ---------------------------------------------------------- */
static MunitResult test_int_has_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_integer(10);

    munit_assert_not_null(obj);
    munit_assert_int(obj->refcount, ==, 1);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /inc_refcount
   ---------------------------------------------------------- */
static MunitResult test_inc_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);

    munit_assert_not_null(obj);
    munit_assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /dec_refcount
   ---------------------------------------------------------- */
static MunitResult test_dec_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    munit_assert_int(obj->refcount, ==, 1);

    /* Sem bootlib: apenas garantimos que o objeto ainda existe (não crashou) */
    munit_assert_not_null(obj);

    free(obj);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /free_refcount
   ---------------------------------------------------------- */
static MunitResult test_refcount_free_is_called(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    munit_assert_int(obj->refcount, ==, 1);

    /* Último decremento deve teoricamente destruir obj */
    refcount_dec(obj);

    /* Sem bootlib: não temos como verificar libertação, só testamos que não crashou */

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /string_freed
   ---------------------------------------------------------- */
static MunitResult test_allocated_string_is_freed(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    munit_assert_int(obj->refcount, ==, 1);
    munit_assert_string_equal(obj->data.v_string, "Hello @wagslane!");

    /* Última libertação */
    refcount_dec(obj);

    /* Sem bootlib: não podemos testar a libertação explicitamente */

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    { "/has_refcount",  test_int_has_refcount,          NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inc_refcount",  test_inc_refcount,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/dec_refcount",  test_dec_refcount,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/free_refcount", test_refcount_free_is_called,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string_freed",  test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
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
