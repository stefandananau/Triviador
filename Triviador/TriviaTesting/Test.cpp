#define BOOST_TEST_MODULE mytests


#include <cpr/cpr.h>

#include "Server.h"
#include "QuestionMultipleChoiceRecord.h"
#include "QuestionMultipleChoice.h"
#include "QuestionNumericRecord.h"
#include "QuestionNumeric.h"


#include <boost/test/unit_test.hpp>


class TestFixture: public Server {
	
	/*TestFixture() :s_instance() { BOOST_TEST_MESSAGE("setup fixture"); };
	~TestFixture() {};
	Server s_instance;*/
};

BOOST_AUTO_TEST_SUITE(Test_Converter)

	BOOST_AUTO_TEST_CASE(QuestionMultipleChoice_To_QuestionMultipleChoiceRecord) {

	QuestionMultipleChoice TestQuestionMultipleChoice(std::string("Random Category"), std::string("Multiple"),std::string("Easy"),std::string("Random Question"),std::string("Correct Answer"),{std::string("Wrong Answer 1"),std::string("Wrong Answer 2") ,std::string("Wrong Answer 3") });
	QuestionMultipleChoiceRecord TestQuestionMultipleChoiceRecord(TestQuestionMultipleChoice);
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_type, TestQuestionMultipleChoice.GetType());
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_question, TestQuestionMultipleChoice.GetQuestion());
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_correctAnswer, TestQuestionMultipleChoice.GetCorrectAnswer());
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_wrongAnswer1, TestQuestionMultipleChoice.GetIncorrectAnswers()[0]);
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_wrongAnswer2, TestQuestionMultipleChoice.GetIncorrectAnswers()[1]);
	BOOST_REQUIRE_EQUAL(TestQuestionMultipleChoiceRecord.m_wrongAnswer3, TestQuestionMultipleChoice.GetIncorrectAnswers()[2]);
}

	BOOST_AUTO_TEST_CASE(QuestionNumeric_To_QuestionNumericRecord) {

	QuestionNumeric TestQuestionNumeric(std::string("Random Category"), std::string("Numeric"), std::string("Easy"), std::string("Random Question"), uint8_t(1));
	QuestionNumericRecord TestQuestionNumericRecord(TestQuestionNumeric);
	BOOST_REQUIRE_EQUAL(TestQuestionNumericRecord.m_type, TestQuestionNumeric.GetType());
	BOOST_REQUIRE_EQUAL(TestQuestionNumericRecord.m_question, TestQuestionNumeric.GetQuestion());
	BOOST_REQUIRE_EQUAL(uint8_t(stoi(TestQuestionNumericRecord.m_correctAnswer)), TestQuestionNumeric.GetCorrectAnswer());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(Test_Server_Routes, TestFixture)

	BOOST_AUTO_TEST_CASE(Test_Database_Route)
	{
	crow::request reqTableMultipleChoice;
	crow::request reqTableNumeric;
	crow::request reqTableUser;
	crow::request reqTableAll;
	crow::response rep;
	reqTableMultipleChoice.url = reqTableNumeric.url = reqTableUser.url= reqTableAll.url = "/database";

	reqTableMultipleChoice.raw_url = "/database?table=QuestionMultipleChoice";
	reqTableMultipleChoice.url_params = { "/database?table=QuestionMultipleChoice" };

	reqTableNumeric.raw_url = "/database?table=QuestionNumeric";
	reqTableNumeric.url_params = { "/database?table=QuestionNumeric" };

	reqTableUser.raw_url = "/database?table=User";
	reqTableUser.url_params = { "/database?table=User" };

	reqTableAll.raw_url = "/database?table=All";
	reqTableAll.url_params = { "/database?table=All" };

	Server s;
	s.PopulateServerDatabase();

	rep = DataBaseRoute(reqTableMultipleChoice);
	if (rep.code != 200)
		BOOST_ERROR("Error : QuestionMultipleChoice");
	rep.clear();

	rep = DataBaseRoute(reqTableNumeric);
	if (rep.code != 200)
		BOOST_ERROR("Error : QuestionNumeric");
	rep.clear();	
	
	rep = DataBaseRoute(reqTableUser);
	if (rep.code != 200)
		BOOST_ERROR("Error : User");
	rep.clear();	
	
	rep = DataBaseRoute(reqTableAll);
	if (rep.code != 200)
		BOOST_ERROR("Error : All");
	rep.clear();
	}

	BOOST_AUTO_TEST_CASE(Test_Return_Random_Question_Route)
	{
		crow::request reqRandomMultiple;
		crow::request reqRandomNumeric;
		crow::response rep;
		reqRandomMultiple.url = reqRandomNumeric.url = "/database/getQuestion";

		reqRandomMultiple.raw_url = "/database/getQuestion?type=Multiple";
		reqRandomMultiple.url_params = { "/database/getQuestion?type=Multiple" };

		reqRandomNumeric.raw_url = "/database/getQuestion?type=Numeric";
		reqRandomNumeric.url_params = { "/database/getQuestion?type=Numeric" };

		Server s;
		s.PopulateServerDatabase();
		std::default_random_engine generator;

		rep = ReturnRandomQuestionRoute(reqRandomMultiple,generator);
		if (rep.code != 200&&!rep.body.empty())
			BOOST_ERROR("Error : Multiple");
		rep.clear();

		rep = ReturnRandomQuestionRoute(reqRandomNumeric, generator);
		if (rep.code != 200 && !rep.body.empty())
			BOOST_ERROR("Error : Numeric");
		rep.clear();

	}
	BOOST_AUTO_TEST_CASE(Test_Authentication_Route)
	{
		crow::request reqLogin;
		crow::request reqRegister;
		crow::response rep;
		reqLogin.url = reqRegister.url = "/authentication";

		reqLogin.raw_url = "/authentication?login&email=admin@admin.com&password=admin";
		reqLogin.url_params = { "/authentication?login&email=admin@admin.com&password=admin" };

		reqRegister.raw_url = "/authentication?register&email=admin@admin.com&password=admin";
		reqRegister.url_params = { "/authentication?register&email=admin@admin.com&password=admin" };

		rep = AuthenticationRoute(reqLogin);
		if (rep.code != 202 )
			BOOST_ERROR("Error : Login");
		rep.clear();

		rep = AuthenticationRoute(reqRegister);
		if (rep.code == 200)
			BOOST_ERROR("Error : Register");
		rep.clear();
	}


BOOST_AUTO_TEST_SUITE_END();

//BOOST_FIXTURE_TEST_SUITE(TestServerSuite, TestFixture);
//
//BOOST_AUTO_TEST_CASE(serverwipeTestCase) {
//	s_instance.wipeQuestions();
//	s_instance.wipeUsers();
//	BOOST_TEST(
//		s_instance.getNumberOfUserRecords() == 0
//	);
//}
//
//BOOST_AUTO_TEST_SUITE_END();