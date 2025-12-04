#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "snekobject.h"

/* ----------------------------------------------------------
   correctly_free
   ---------------------------------------------------------- */
static MunitResult
test_correctly_free(const MunitParameter params[], void *data) {
    snek_object_t *first = new_snek_array(1);
    snek_object_t *second = new_snek_array(1);

    /* refcounts: first = 1, second = 1 */
    snek_array_set(first, 0, second);
    /* refcounts: first = 1, second = 2 */

    snek_array_set(second, 0, first);
    /* refcounts: first = 2, second = 2 */

    refcount_dec(first);   /* first -> 1 */
    refcount_dec(second);  /* second -> 1 */

    /* Agora, como arrays referenciam-se mutuamente,
       NENHUM fica com refcount 0 automaticamente. */

    munit_assert_int(first->refcount, ==, 1);
    munit_assert_int(second->refcount, ==, 1);

    /* libertar o que falta */
    refcount_dec(first);
    refcount_dec(second);

    return MUNIT_OK;
}

/* ----------------------------------------------------------
   Suite
   ---------------------------------------------------------- */

static MunitTest tests[] = {
    {
        "/correctly_free",
        test_correctly_free,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
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
