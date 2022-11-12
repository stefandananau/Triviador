#pragma once
#include <string>

struct QuestionMultipleChoiceRecord
{
	int id;
	std::string m_question;
	std::string m_correctAnswer;
	std::string m_wrongAnswer1;
	std::string m_wrongAnswer2;
	std::string m_wrongAnswer3;
};
