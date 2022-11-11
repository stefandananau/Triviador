#include "QuestionMultipleChoice.h"

QuestionMultipleChoice::QuestionMultipleChoice():m_category(""),m_type(""), m_correct_answer(""),m_difficulty("")
{


}

QuestionMultipleChoice::QuestionMultipleChoice(const std::string& category, const std::string& type, const std::string& difficulty,const std::string& question,const std::string& correct_answer, const std::vector<std::string>& incorrect_answers):
	m_category(category),
	m_difficulty(difficulty), 
	m_question(question),
	m_correct_answer(correct_answer),
	m_incorrect_answers(incorrect_answers),
	m_type(type)
{
}
void QuestionMultipleChoice::SetCategory(const std::string& category)
{
	m_category = category;
}

void QuestionMultipleChoice::SetType(const std::string& type)
{
	m_type = type;
}

void QuestionMultipleChoice::SetDifficulty(const std::string& difficulty)
{
	m_difficulty = difficulty;
}

void QuestionMultipleChoice::SetCorrectAnswer(const std::string& correct_answer)
{
	m_correct_answer = correct_answer;
}

void QuestionMultipleChoice::SetIncorrectAnswers(const std::vector<std::string>& incorrect_answers)
{
	m_incorrect_answers = incorrect_answers;
}

void QuestionMultipleChoice::SetQuestion(const std::string& question)
{
	m_question = question;
}

void QuestionMultipleChoice::AddIncorrectAnswers(const std::string& incorrect_answer)
{
	m_incorrect_answers.push_back(incorrect_answer);
}

std::string QuestionMultipleChoice::GetCategory() const
{
	return m_category;
}

std::string QuestionMultipleChoice::GetType() const
{
	return m_type;
}

std::string QuestionMultipleChoice::GetDifficulty() const
{
	return m_difficulty;
}

std::string QuestionMultipleChoice::GetCorrectAnswer() const
{
	return m_correct_answer;
}

std::vector<std::string> QuestionMultipleChoice::GetIncorrectAnswers() const
{
	return m_incorrect_answers;
}

std::string QuestionMultipleChoice::GetQuestion() const
{
	return m_question;
}

std::ostream& operator<<(std::ostream& os, const QuestionMultipleChoice& questionMultipleChoice)
{
	os << "Category == " << questionMultipleChoice.m_category << std::endl;
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
