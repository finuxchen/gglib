#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>
#include "gg_array.h"

BOOST_AUTO_TEST_SUITE(gg_array_test_suite)

BOOST_AUTO_TEST_CASE(gg_array_create_test)
{
    BOOST_CHECK_EQUAL(NULL, gg_array_create(0, 0));
}

BOOST_AUTO_TEST_SUITE_END()
