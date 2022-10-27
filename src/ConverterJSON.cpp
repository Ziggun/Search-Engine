#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::fstream finConfig;
    nlohmann::json dict;
    finConfig.exceptions(fstream::badbit | fstream::failbit);
    try
    {
        finConfig.open("config.json");
        finConfig >> dict;
        cout << dict["config"]["name"] << endl;
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        cout << "Config file is missing" << endl;
    }
    std::vector<string> vec_res, vecFiles;
    string findWord;
    string Version = "0.1";
    try
    {
        conf.MaxRes = dict["config"]["max_responses"];
        conf.Version = dict["config"]["version"];
        conf.Name = dict["config"]["name"];
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
        cout << "config file is empty" << endl;
    }
    if(Version != conf.Version)
    {
       clog << "config.json has incorrect file version" << endl;
    }
    vecFiles = dict["files"];
    for (auto file : vecFiles)
    {
        ifstream in(file, std::ios::in);
        if (!in.good())
        {
            std::clog << "Couldn't open file.\n";
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

int ConverterJSON::GetResponsesLimit()  {
    std::fstream test("config.json");
    nlohmann::json dict;
    test >> dict;
    test.close();
    int Resp;
    Resp = dict["config"]["max_responses"];
    return Resp;
};

std::vector<string> ConverterJSON::GetRequests()
{
    std::fstream req("request.json");
    nlohmann::json dict;
    req >> dict;
    req.close();
    std::vector<string> vecRequest;
    vecRequest = dict["requests"];
    return  vecRequest;
};

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>
                               answers)
{
    std::fstream ans("answers.json",ios::out);
    if (!ans.good())
    {
        clog << "Couldn't open file.\n";
    } else
    {
        ans.close();
        std::fstream ans("answers.json");
        nlohmann::json dict;
        for (int i = 0; i < answers.size(); i++)
        {
            dict["answers"];
            string a = "request00" + to_string(i+1);
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
};