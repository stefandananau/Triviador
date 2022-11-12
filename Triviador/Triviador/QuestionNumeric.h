#pragma once
#include <string>
#include <fstream>

class QuestionNumeric
{
public:
	QuestionNumeric();
	QuestionNumeric(const std::string& category,
		const std::string& type,
		const std::string& difficulty,
		const std::string& question,
		uint8_t correct_answer);

	std::string GetCategory() const;
	void SetCategory(const std::string& category);

	std::string GetType() const;
	void SetType(const std::string& type);

	std::string GetDifficulty() const;
	void SetDifficulty(const std::string& difficulty);

	std::string GetQuestion() const;
	void SetQuestion(const std::string& question);

	uint8_t GetCorrectAnswer() const;
	void SetCorrectAnswer(uint8_t correct_answer);

	friend std::ostream& operator<<(std::ostream& os, const QuestionNumeric& question);


private:
	std::string m_category;
	std::string m_type;
	std::string m_difficulty;
	std::string m_question;
	int m_correct_answer;


};

