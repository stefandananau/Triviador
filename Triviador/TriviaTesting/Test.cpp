#define WIN32_LEAN_AND_MEAN
#define BOOST_TEST_MODULE mytests

#include <boost/test/included/unit_test.hpp>
#include "../ServerTriviador/Server.h"



BOOST_AUTO_TEST_CASE(myTestCase)
{
  BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(serverwipeTestCase) {
	Server sTest;
	sTest.wipeQuestions();
	sTest.wipeUsers();
	BOOST_TEST(
		sTest.getNumberOfUserRecords() == 0
	);
}