#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <thread>
#include "nlohmann/json.hpp"
#include <mutex>

using json = nlohmann::json;
using namespace std;

class ConverterJSON
{
public:
	ConverterJSON() = default;
	std::vector<std::string> GetTextDocuments();
    std::vector<string> GetRequests() const;
	int GetResponsesLimit() const;
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers) const;
};

