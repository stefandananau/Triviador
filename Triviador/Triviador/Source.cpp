#include <iostream>
#include "QuestionMultipleChoice.h"
#include "QuestionNumeric.h"


int main()
{	

	std::string category = "sports";
	std::string type = "sports";
	std::string difficulty = "sports";
	std::string question = "sports";
	std::string correctAnswer = "sports";
	std::vector<std::string> incorrectAnswers = {"da","nu","poate"};
	

	QuestionMultipleChoice qmc;
	QuestionMultipleChoice qmc2( category, type, difficulty, question, correctAnswer,incorrectAnswers);


	QuestionNumeric qn;
	
	std::cout << qmc<<std::endl<<qmc2;
	
	qn.SetQuestion("da");
	
	std::cout << qn;
	return 0;
}