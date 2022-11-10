#pragma once
#include<string>
#include<vector>
#include<fstream>
class QuestionMultipleChoice
{
public:
	QuestionMultipleChoice();
	QuestionMultipleChoice(std::string category,
		std::string type,
		std::string difficulty,
		std::string question,
		std::string correct_answer,
		std::vector<std::string> incorrect_answers);


	void setCategory(const std::string& category);
	void setType(const std::string& type);
	void setDifficulty(const std::string& difficulty);
	void setCorrectAnswer(const std::string& correct_answer);
	void setIncorrectAnswers(const std::vector<std::string>& incorrect_answers);
	void setQuestion(const std::string& question);

	void addIncorrectAnswers(const std::string& incorrect_answer);

	friend std::ostream& operator<<(std::ostream& os, const QuestionMultipleChoice& questionMultipleChoice);

private:
	std::string m_category;
	std::string m_type;
	std::string m_difficulty;
	std::string m_question;
	std::string m_correct_answer;
	std::vector<std::string> m_incorrect_answers;

};

