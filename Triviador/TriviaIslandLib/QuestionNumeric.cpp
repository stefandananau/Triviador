#include "QuestionNumeric.h"

QuestionNumeric::QuestionNumeric() :m_category(""), m_type(""), m_correctAnswer(0), m_difficulty("")
{


}

QuestionNumeric::QuestionNumeric(const std::string& category, const std::string& type,const std::string& difficulty,const std::string& question, uint8_t correctAnswer):m_category(category),m_correctAnswer(correctAnswer),m_difficulty(difficulty),m_type(type)
{
}

std::string QuestionNumeric::GetCategory() const
{
    return m_category;
}

void QuestionNumeric::SetCategory(const std::string& category)
{
    m_category = category;
}

std::string QuestionNumeric::GetType() const
{
    return m_type;
}

void QuestionNumeric::SetType(const std::string& type)
{
    m_type = type;
}

std::string QuestionNumeric::GetDifficulty() const
{
    return m_difficulty;
}

void QuestionNumeric::SetDifficulty(const std::string& difficulty)
{
    m_difficulty = difficulty;
}

std::string QuestionNumeric::GetQuestion() const
{
    return m_question;
}

void QuestionNumeric::SetQuestion(const std::string& question)
{
    m_question = question;
}

uint8_t QuestionNumeric::GetCorrectAnswer() const
{
    return m_correctAnswer;
}

void QuestionNumeric::SetCorrectAnswer(uint8_t correctAnswer)
{
    m_correctAnswer = correctAnswer;
}

std::ostream& operator<<(std::ostream& os, const QuestionNumeric& questionNumeric)
{
    os << "Category == " << questionNumeric.m_category << std::endl;
    os << "Type == " << questionNumeric.m_type << std::endl;
    os << "Difficulty == " << questionNumeric.m_difficulty << std::endl;
    os << "Question == " << questionNumeric.m_question << std::endl;
    os << "Correct Answer == " << questionNumeric.m_correctAnswer << std::endl;
    return os;
}
