#define CURLPP_STATICLIB
#define URL "https://opentdb.com/api.php?amount=50&type=multiple"

#include <curl/curl.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool isNumber(const std::string& s_toCheck) {
	for (const char& c : s_toCheck) {
		if (!std::isdigit(c))
			return false;
	}
	return true;
}

int main() {
	CURL* curl;
	CURLcode res;
	int countQuestions = 0;
	uint16_t countNumericalQuestions = 0;
	std::string readBuffer;
	std::string::size_type position = 0;

	curl_global_init(CURL_GLOBAL_ALL);


	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		std::string questionNumberSubstring = std::string("\"question\":");

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cout << " curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
			return -1;
		}

		json finalJsonNumerical;
		json finalJsonMultipleChoiceQuestions;

		json numericalQuestions;
		json multipleChoiceQuestions;

		uint16_t indexNumerical = 0;
		uint16_t indexMultipleChoice = 0;
		uint16_t curlReqCode;

		while ((indexNumerical < 50) || (indexMultipleChoice < 50)) {
			readBuffer.clear();
			res = curl_easy_perform(curl);
			if (res != CURLE_OK) {
				std::cout << " curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
				return -1;
			}

			json readJson = json::parse(readBuffer);
			for (int i = 0; i < 50; i++) {
				if (isNumber(readJson["results"][i]["correct_answer"])) {
					readJson["results"][i]["type"] = "numerical";
					++countNumericalQuestions;
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

		outNumerical << "Number_of_questions: " << finalJsonNumerical["results"].size() << "\n";
		outMultipleChoice << "Number_of_questions: " << finalJsonMultipleChoiceQuestions["results"].size() << "\n";

		outNumerical << finalJsonNumerical;
		outMultipleChoice << finalJsonMultipleChoiceQuestions;

		outNumerical.close();
		outMultipleChoice.close();

	}
	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return 0;

}