#define CURLPP_STATICLIB

#include <cpr/cpr.h>

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>


#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace requester {
	bool isNumber(const std::string& s_toCheck) {
		for (const char& c : s_toCheck) {
			if (!std::isdigit(c))
				return false;
		}
		return true;
	}


	//test
	int toUTF8(std::string& s) {
		size_t htmlPos = 0;
		size_t entries = 0;
		
		std::map<std::string, char> htmlToUtf8_map;
		htmlToUtf8_map.insert(std::make_pair("&quot;", '\"'));
		htmlToUtf8_map.insert(std::make_pair("&#039;", '\''));



		for (const auto& chr : htmlToUtf8_map) {
			while (htmlPos = s.find(chr.first) != std::string::npos) {
				s.replace(s.find(chr.first), chr.first.length(), std::string(1, chr.second));
				htmlPos += chr.first.length();
				entries++;
			}

		}
		return entries;
	}
};



int main() {

	cpr::Response response;

	int countQuestions = 0;
	uint16_t countNumericalQuestions = 0;
	std::string readBuffer;
	std::string::size_type position = 0;


	std::string questionNumberSubstring = std::string("\"question\":");

	json finalJsonNumerical;
	json finalJsonMultipleChoiceQuestions;

	json numericalQuestions;
	json multipleChoiceQuestions;

	uint16_t indexNumerical = 0;
	uint16_t indexMultipleChoice = 0;
	uint16_t curlReqCode;

	json readJson;
	std::string URL;

	std::cout << "Please enter a valid API URL generated from opentdb.com/api_config.php: ";
	std::cin >> URL;

	while ((indexNumerical < 50) || (indexMultipleChoice < 50)) {
		response = cpr::Get(cpr::Url{ URL });

		if (response.status_code != 200) {
			std::cout << "Unable to contact opentdb.com! Exiting...\n";
			exit(-1);
		}
		readBuffer.clear();
		readBuffer = response.text;

		//JSON DOES NOT SUPPORT "\'" and "\"", DO NOT USE! >:(
		//requester::toUTF8(readBuffer
		//std::cout << readBuffer;
		//PARSE OUT HTML CHARS WHEN PRINTING QUESTIONS TO GUY

		readJson = json::parse(readBuffer);
		if (readJson["response_code"] != 0) {
			std::cout << "Please run the program again using a valid opentdb.com API URL!\nHead over to 'https://opentdb.com/api_config.php' and generate a valid API URL.\n";
			exit(-1);
		}	
		for (int i = 0; i < 50; i++) {
			if (requester::isNumber(readJson["results"][i]["correct_answer"])) {
				readJson["results"][i]["type"] = "numerical";
			}
		}

		for (int i = 0; i < 50; i++) {
			if ((readJson["results"][i]["type"] == "numerical") && (indexNumerical < 50)) {
				numericalQuestions.push_back(readJson["results"][i]);
				indexNumerical++;
			}
			else if (indexMultipleChoice < 50) {
				multipleChoiceQuestions.push_back(readJson["results"][i]);
				indexMultipleChoice++;
			}
		}
		curlReqCode = readJson["response_code"];
	}

	finalJsonNumerical["response_code"] = curlReqCode;
	finalJsonNumerical["results"] = numericalQuestions;


	finalJsonMultipleChoiceQuestions["response_code"] = curlReqCode;
	finalJsonMultipleChoiceQuestions["results"] = multipleChoiceQuestions;


	std::cout << "\n_______________________________\n";
	std::cout << "No. questions: " << finalJsonMultipleChoiceQuestions["results"].size() + finalJsonNumerical["results"].size() << "\n";
	std::cout << "No. numerical_questions: " << indexNumerical << "\n";
	std::cout << "No. multiple_choice_questions: " << indexMultipleChoice << "\n";
	std::cout << "_________________________________\n";

	std::ofstream outNumerical("dataNumerical.json");
	std::ofstream outMultipleChoice("dataMultipleChoice.json");

	//outNumerical << "Number_of_questions: " << finalJsonNumerical["results"].size() << "\n";
	//outMultipleChoice << "Number_of_questions: " << finalJsonMultipleChoiceQuestions["results"].size() << "\n";

	outNumerical << finalJsonNumerical;
	outMultipleChoice << finalJsonMultipleChoiceQuestions;

	outNumerical.close();
	outMultipleChoice.close();

	return 0;
}
