#include <iostream>
#include "QuestionMultipleChoice.h"
#include "QuestionNumeric.h"
#include "Storage.h"
#include "Parser.h"

int main()
{	
//
//	std::string category = "sports";
//	std::string type = "sports";
//	std::string difficulty = "sports";
//	std::string question = "sports";
//	std::string correctAnswer = "sports";
//	std::vector<std::string> incorrectAnswers = {"da","nu","poate"};
//	
//
//	QuestionMultipleChoice qmc;
//	QuestionMultipleChoice qmc2( category, type, difficulty, question, correctAnswer,incorrectAnswers);
//
//
//	QuestionNumeric qn;
//	
//	std::cout << qmc<<std::endl<<qmc2;
//	
//	qn.SetQuestion("da");
//
//	Storage db("testDB.sqlite");
//	db.Sync();
//	UserRecord u{ -1,"ceva@gmail.com","1234" };
//	db.AddUser(u);
//	db.PrintUsers();
//	std::cout << qn;
//	return 0;

	auto p = parser::ParserJsonMultiple();
	for (const auto& q : p) {
		std::cout << q << std::endl;
	}
}
