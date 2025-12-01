#include <stdlib.h>
#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   /returns_null
   ---------------------------------------------------------- */
static MunitResult test_returns_null(const MunitParameter params[], void *data) {
    snek_object_t *vec = new_snek_vector3(NULL, NULL, NULL);
    munit_assert_ptr_null(vec);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /multiple_objects
   ---------------------------------------------------------- */
static MunitResult test_vec_multiple_objects(const MunitParameter params[], void *data) {
    snek_object_t *x = new_snek_integer(1);
    snek_object_t *y = new_snek_integer(2);
    snek_object_t *z = new_snek_integer(3);
    snek_object_t *vec = new_snek_vector3(x, y, z);

    munit_assert_ptr_not_null(vec);
    munit_assert_ptr(x, ==, vec->data.v_vector3.x);
    munit_assert_ptr(y, ==, vec->data.v_vector3.y);
    munit_assert_ptr(z, ==, vec->data.v_vector3.z);

    munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
    munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
    munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 3);

    free(x);
    free(y);
    free(z);
    free(vec);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   /same_object
   ---------------------------------------------------------- */
static MunitResult test_vec_same_object(const MunitParameter params[], void *data) {
    snek_object_t *i = new_snek_integer(1);
    snek_object_t *vec = new_snek_vector3(i, i, i);

    munit_assert_ptr_not_null(vec);
    munit_assert_ptr(i, ==, vec->data.v_vector3.x);
    munit_assert_ptr(i, ==, vec->data.v_vector3.y);
    munit_assert_ptr(i, ==, vec->data.v_vector3.z);

    munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 1);
    munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 1);
    munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 1);

    // Update value
    i->data.v_int = 2;
    munit_assert_int(vec->data.v_vector3.x->data.v_int, ==, 2);
    munit_assert_int(vec->data.v_vector3.y->data.v_int, ==, 2);
    munit_assert_int(vec->data.v_vector3.z->data.v_int, ==, 2);

    free(i);
    free(vec);
    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Lista de testes
   ---------------------------------------------------------- */
static MunitTest tests[] = {
    { "/returns_null", test_returns_null, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/multiple_objects", test_vec_multiple_objects, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/same_object", test_vec_same_object, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* ----------------------------------------------------------
   Suite
   ---------------------------------------------------------- */
static const MunitSuite suite = {
    "/object-vector",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

/* ----------------------------------------------------------
   Main
   ---------------------------------------------------------- */
int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
