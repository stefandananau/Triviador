#define BOOST_TEST_MODULE mytests

#include "Server.h"
#include <boost/test/unit_test.hpp>


struct TestFixture {
	Server s_instance;
	TestFixture() :s_instance() {}
	~TestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestServerSuite, TestFixture);

BOOST_AUTO_TEST_CASE(serverwipeTestCase) {
	s_instance.wipeQuestions();
	s_instance.wipeUsers();
	BOOST_TEST(
		s_instance.getNumberOfUserRecords() == 0
	);
}

BOOST_AUTO_TEST_SUITE_END();