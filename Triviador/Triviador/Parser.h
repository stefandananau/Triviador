#pragma once
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "QuestionMultipleChoice.h"
#include "QuestionNumeric.h"
using json = nlohmann::json;

std::vector<QuestionMultipleChoice> ParserJsonMultiple();
std::vector<QuestionNumeric> ParserJsonNumeric();