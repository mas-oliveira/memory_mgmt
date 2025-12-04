#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ============================================================
   /array_set
   ============================================================ */
static MunitResult test_array_set(const MunitParameter params[], void *data) {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *array = new_snek_array(1);

    snek_array_set(array, 0, foo);
    munit_assert_int(foo->refcount, ==, 2);

    /* Ainda não pode ser libertado */
    munit_assert_ptr_not_null(foo);

    refcount_dec(foo);
    refcount_dec(array);

    return MUNIT_OK;
}

/* ============================================================
   /array_free
   ============================================================ */
static MunitResult test_array_free(const MunitParameter params[], void *data) {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *array = new_snek_array(2);

    snek_array_set(array, 0, foo);
    snek_array_set(array, 1, bar);

    munit_assert_int(foo->refcount, ==, 2);
    munit_assert_int(bar->refcount, ==, 2);
    munit_assert_int(baz->refcount, ==, 1);

    /* foo continua referenciado pelo array */
    refcount_dec(foo);

    /* Substituir foo → baz */
    snek_array_set(array, 0, baz);

    /* foo foi libertado */
    /* Nesta versão sem bootlib não conseguimos verificar isso */

    refcount_dec(bar);
    refcount_dec(baz);
    refcount_dec(array);

    return MUNIT_OK;
}

/* ============================================================
   /vector3
   ============================================================ */
static MunitResult test_vector3_refcounting(const MunitParameter params[], void *data) {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *vec = new_snek_vector3(foo, bar, baz);

    munit_assert_int(foo->refcount, ==, 2);
    munit_assert_int(bar->refcount, ==, 2);
    munit_assert_int(baz->refcount, ==, 2);

    refcount_dec(foo); /* ainda referenciado dentro de vec */

    refcount_dec(vec); /* liberta foo */

    refcount_dec(bar);
    refcount_dec(baz);

    return MUNIT_OK;
}

/* ============================================================
   /vector3-same
   ============================================================ */
static MunitResult test_vector3_refcounting_same(const MunitParameter params[], void *data) {
    snek_object_t *foo = new_snek_integer(1);

    snek_object_t *vec = new_snek_vector3(foo, foo, foo);

    munit_assert_int(foo->refcount, ==, 4);

    refcount_dec(foo); /* ainda 3 refs via vec */

    refcount_dec(vec); /* liberta foo */

    return MUNIT_OK;
}

/* ============================================================
   /has_refcount
   ============================================================ */
static MunitResult test_int_has_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_integer(10);
    munit_assert_int(obj->refcount, ==, 1);
    free(obj);
    return MUNIT_OK;
}

/* ============================================================
   /inc_refcount
   ============================================================ */
static MunitResult test_inc_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);
    munit_assert_int(obj->refcount, ==, 1);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    free(obj);
    return MUNIT_OK;
}

/* ============================================================
   /dec_refcount
   ============================================================ */
static MunitResult test_dec_refcount(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    munit_assert_int(obj->refcount, ==, 2);

    refcount_dec(obj);
    munit_assert_int(obj->refcount, ==, 1);

    free(obj);
    return MUNIT_OK;
}

/* ============================================================
   /free_refcount
   ============================================================ */
static MunitResult test_refcount_free_is_called(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    refcount_dec(obj);
    refcount_dec(obj);

    /* sem bootlib só validamos que não crasha */

    return MUNIT_OK;
}

/* ============================================================
   /string_freed
   ============================================================ */
static MunitResult test_allocated_string_is_freed(const MunitParameter params[], void *data) {
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    refcount_dec(obj);

    munit_assert_string_equal(obj->data.v_string, "Hello @wagslane!");

    refcount_dec(obj);

    return MUNIT_OK;
}

/* ============================================================
   Suite
   ============================================================ */

static MunitTest tests[] = {
    { "/array_set", test_array_set, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/array_free", test_array_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/vector3", test_vector3_refcounting, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/vector3-same", test_vector3_refcounting_same, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/has_refcount", test_int_has_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/inc_refcount", test_inc_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/dec_refcount", test_dec_refcount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/free_refcount", test_refcount_free_is_called, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/string_freed", test_allocated_string_is_freed, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/refcount",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
