#pragma once
#include <string>
#include "QuestionNumeric.h"

struct QuestionNumericRecord
{
	int id;
	std::string m_type;
	std::string m_question;
	std::string m_answer;

	QuestionNumericRecord(const QuestionNumeric& qn):
		id(-1),m_type(qn.GetType()),
		m_question(qn.GetQuestion()),
		m_answer(std::to_string(qn.GetCorrectAnswer()))
	{}

	QuestionNumericRecord() :m_type("NaN"), m_question("NaN"), m_answer("NaN") {};

};
