#pragma once
#include <string>
#include "QuestionNumeric.h"

struct QuestionNumericRecord
{
	int id;
	std::string m_question;
	std::string m_answer;

	QuestionNumericRecord(const QuestionNumeric& qn):m_question(qn.GetQuestion()),m_answer(std::to_string(qn.GetCorrectAnswer()))
	{}

};
