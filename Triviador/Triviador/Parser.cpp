#include "Parser.h"

std::vector<QuestionMultipleChoice>parser::ParserJsonMultiple() {
	std::ifstream f("dataMultipleChoice.json");

	if (f.is_open())
	{
		json dataMultipleChoice = json::parse(f);

		if (dataMultipleChoice.contains("response_code"))
		{
			dataMultipleChoice.erase("response_code");
		}
		std::vector<QuestionMultipleChoice> q_m_c;

		for (const auto& obj : dataMultipleChoice["results"].items())
		{
			QuestionMultipleChoice currentQuestion;

			for (const auto& val : obj.value().items())
			{
				if (val.key() == "category")
				{
					currentQuestion.SetCategory(val.value());
				}
				else if (val.key() == "type")
				{
					currentQuestion.SetType(val.value());
				}
				else if (val.key() == "question")
				{
					currentQuestion.SetQuestion(val.value());
				}
				else if (val.key() == "correct_answer")
				{
					currentQuestion.SetCorrectAnswer(val.value());
				}
				else if (val.key() == "incorrect_answers")
				{

					for (const auto& wrongQuestion : val.value().items())
					{

						currentQuestion.AddIncorrectAnswers(wrongQuestion.value());
					}
				}
			}
			q_m_c.push_back(currentQuestion);
		}
		return  q_m_c;
	}
	else
	{
		throw std::out_of_range("Json file failed to open\nCheck if name is correct\n");
	}
}

std::vector<QuestionNumeric> parser::ParserJsonNumeric() {
	std::ifstream f("dataNumeric.json");

	if (f.is_open())
	{
		json dataNumeric = json::parse(f);

		if (dataNumeric.contains("response_code"))
		{
			dataNumeric.erase("response_code");
		}
		std::vector<QuestionNumeric> q_n;

		for (const auto& obj : dataNumeric["results"].items())
		{
			QuestionNumeric currentQuestion;

			for (const auto& val : obj.value().items())
			{
				if (val.key() == "category")
				{
					currentQuestion.SetCategory(val.value());
				}
				else if (val.key() == "type")
				{
					currentQuestion.SetType(val.value());
				}
				else if (val.key() == "question")
				{
					currentQuestion.SetQuestion(val.value());
				}
				else if (val.key() == "correct_answer")
				{
					currentQuestion.SetCorrectAnswer(val.value());
				}
			}
			q_n.push_back(currentQuestion);
		}
		return  q_n;
	}
	else
	{
		throw std::out_of_range("Json file failed to open\nCheck if name is correct\n");
	}
}
