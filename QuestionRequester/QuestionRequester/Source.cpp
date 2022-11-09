#define CURLPP_STATICLIB
#define URL "https://opentdb.com/api.php?amount=50&type=multiple"

#include <curl/curl.h>

#include <string>
#include <iostream>


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int main() {
	CURL* curl;
	CURLcode res;

	std::string readBuffer;


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
		std::cout << readBuffer;
	}
	return 0;
}