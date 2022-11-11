#pragma once
#include<string>
#include<vector>
#include<fstream>
class QuestionMultipleChoice
{
public:
	QuestionMultipleChoice();
	QuestionMultipleChoice(const std::string& category,
		const std::string& type,
		const std::string& difficulty,
		const std::string& question,
		const std::string& correct_answer,
		const std::vector<std::string>& incorrect_answers);



	void SetCategory(const std::string& category);
	std::string GetCategory()const;

	void SetType(const std::string& type);
	std::string GetType()const;

	void SetDifficulty(const std::string& difficulty);
	std::string GetDifficulty()const;

	void SetCorrectAnswer(const std::string& correct_answer);
	std::string GetCorrectAnswer()const;

	void SetIncorrectAnswers(const std::vector<std::string>& incorrect_answers);
	std::vector<std::string> GetIncorrectAnswers()const;

	void SetQuestion(const std::string& question);
	std::string GetQuestion()const;

	void AddIncorrectAnswers(const std::string& incorrect_answer);





	friend std::ostream& operator<<(std::ostream& os, const QuestionMultipleChoice& questionMultipleChoice);

private:
	std::string m_category;
	std::string m_type;
	std::string m_difficulty;
	std::string m_question;
	std::string m_correct_answer;
	std::vector<std::string> m_incorrect_answers;

};

