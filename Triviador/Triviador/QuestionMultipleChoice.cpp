#include "QuestionMultipleChoice.h"

QuestionMultipleChoice::QuestionMultipleChoice()
{
	m_category = "";
	m_type = "";
	m_difficulty = "";
	m_correct_answer = "";

}

QuestionMultipleChoice::QuestionMultipleChoice(std::string category, std::string type, std::string difficulty, std::string question, std::string correct_answer, std::vector<std::string> incorrect_answers) :m_category(category), m_difficulty(difficulty), m_question(question), m_correct_answer(correct_answer), m_incorrect_answers(incorrect_answers), m_type(type)
{
}
void QuestionMultipleChoice::setCategory(const std::string& category)
{
	m_category = category;
}

void QuestionMultipleChoice::setType(const std::string& type)
{
	m_type = type;
}

void QuestionMultipleChoice::setDifficulty(const std::string& difficulty)
{
	m_difficulty = difficulty;
}

void QuestionMultipleChoice::setCorrectAnswer(const std::string& correct_answer)
{
	m_correct_answer = correct_answer;
}

void QuestionMultipleChoice::setIncorrectAnswers(const std::vector<std::string>& incorrect_answers)
{
	m_incorrect_answers = incorrect_answers;
}

void QuestionMultipleChoice::setQuestion(const std::string& question)
{
	m_question = question;
}

void QuestionMultipleChoice::addIncorrectAnswers(const std::string& incorrect_answer)
{
	m_incorrect_answers.push_back(incorrect_answer);
}

std::ostream& operator<<(std::ostream& os, const QuestionMultipleChoice& questionMultipleChoice)
{
	os << "Category == " << questionMultipleChoice.m_category << std::endl;
	os << "Type == " << questionMultipleChoice.m_type << std::endl;
	os << "Difficulty == " << questionMultipleChoice.m_difficulty << std::endl;
	os << "Question == " << questionMultipleChoice.m_question << std::endl;
	os << "Correct Answer == " << questionMultipleChoice.m_correct_answer << std::endl;
	os << "Incorrect Answers == ";
	for (const auto& i_a : questionMultipleChoice.m_incorrect_answers)
	{
		os << i_a << " ";
	}
	os << std::endl << std::endl;
	return os;
}
