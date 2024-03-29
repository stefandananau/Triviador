#pragma once
#include <string>
#include "QuestionMultipleChoice.h"

struct QuestionMultipleChoiceRecord
{
	int id;
	std::string m_type;
	std::string m_question;
	std::string m_correctAnswer;
	std::string m_wrongAnswer1;
	std::string m_wrongAnswer2;
	std::string m_wrongAnswer3;

	QuestionMultipleChoiceRecord(const QuestionMultipleChoice& qmc ):id(-1),
		m_question(qmc.GetQuestion()),
	m_type(qmc.GetType()),
	m_correctAnswer(qmc.GetCorrectAnswer()),
	m_wrongAnswer1(qmc.GetIncorrectAnswers()[0]),
	m_wrongAnswer2(qmc.GetIncorrectAnswers()[1]),
	m_wrongAnswer3(qmc.GetIncorrectAnswers()[2])

	{}

	QuestionMultipleChoiceRecord():m_type("NaN"), m_correctAnswer("NaN"), m_wrongAnswer1("NaN"), m_wrongAnswer2("NaN"), m_wrongAnswer3("NaN") {}
};
