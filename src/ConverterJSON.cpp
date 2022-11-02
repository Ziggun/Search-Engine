#include "ConverterJSON.h"

std::filesystem::path ConfigFile = "config.json";
std::filesystem::path RequestFile = "request.json";
const string AnswersFile = "answers.json";

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::fstream finConfig;
    nlohmann::json dict;
    finConfig.exceptions(fstream::badbit | fstream::failbit);
    try
    {
        finConfig.open(ConfigFile);
        finConfig >> dict;
        cout << "Name of project : " << dict["config"]["name"] << endl;
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        cout << "Config file is missing" << endl;
    }
    std::vector<string> vec_res, vecFiles;
    string findWord;
    string Version = "0.1";
    if(dict["config"]["name"] == nullptr) {
        clog << "Invalid data in file Config.json" << endl;
    } else
    {
        if(Version != dict["config"]["version"])
        {
            clog << "Config.json has incorrect file version\n" << endl;
        }
        vecFiles = dict["files"];
    }
    for (const auto &file : vecFiles)
    {
        ifstream in(file, std::ios::in);
        if (!in.good())
        {
            std::clog << "Couldn't open file. Config.json [files][your files]\n";
        } else
        {
            string test = "";
            while (!in.eof())
            {
                findWord = "";
                in >> findWord;
                test += findWord + " ";
            }
            vec_res.push_back(test);
            in.clear();
        }
    }
    finConfig.close();
    return vec_res;
};

int ConverterJSON::GetResponsesLimit() const
{
    std::fstream test(ConfigFile);
    nlohmann::json dict;
    test >> dict;
    test.close();
    if (dict["config"]["max_responses"] < 1) {
        std::clog << "The number of requests can't be less than 1 \n";
        dict["config"]["max_responses"] = 5;
    }
        return dict["config"]["max_responses"];
};

std::vector<string> ConverterJSON::GetRequests() const
{
    std::fstream req(RequestFile);
    nlohmann::json dict;
    req >> dict;
    req.close();
    std::vector<string> vecRequest;
    vecRequest = dict["requests"];
    return vecRequest;
};

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>
                               answers) const
{
    std::fstream ans(AnswersFile,ios::out);
    if (!ans.good())
    {
        clog << "Couldn't open file Answer.json.\n";
    } else
    {
        nlohmann::json dict;
        for (int i = 0; i < answers.size(); i++)
        {
            dict["answers"];
            string a = "request_00";
            if(i < 9) {
                a += to_string(i + 1);
            } else  if (i < 99)
            {
                a = "request_0" + to_string(i + 1);
            } else
            {
                a = "request_" + to_string(i + 1);
            }
            dict["answers"][a];
            sort(answers[i].begin(), answers[i].end(),
                      [](const auto& x, const auto& y) { return x.second > y.second; });
            if (answers[i].size() > 0)
            {
                dict["answers"][a]["result"] = true;
                for (int j = 0; j < answers[i].size(); j++) {
                    dict["answers"][a]["revelance"];
                    if (answers[i][j].second > 0) {
                        dict["answers"][a]["revelance"].push_back({ {"docId",answers[i][j].first}, {"rank",answers[i][j].second} });
                    }
                }
            } else
            {
                dict["answers"][a]["result"] = false;
            }
        };
        ans << dict.dump(1);
        ans.close();
    }
}
