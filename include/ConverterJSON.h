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

using json = nlohmann::json;
using namespace std;

struct Conf
{
	int MaxRes;
	string Name;
	string Version;
};

class ConverterJSON
{
public:
	ConverterJSON() = default;
	std::vector<std::string> GetTextDocuments();
    std::vector<string> GetRequests();
	int GetResponsesLimit();
	void putAnswers(std::vector<std::vector<std::pair<int, float>>>
		answers);
	Conf conf;
};

