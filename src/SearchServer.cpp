#include "SearchServer.h"

std::vector <RelativeIndex> SearchServer::uniqueWords(multimap<float,int> sR) {
    std::vector<RelativeIndex> vRI;
    std::vector<float> Relevance;
    std::vector<vector<int>> Num;
    std::vector <int> vNum;
    int Iterator = 0;
    float f = 0.0f;

    for (auto s : sR)
    {
        if (Iterator> 0)
        {
            if (s.first != f)
            {
                Relevance.push_back(s.first);
                Num.push_back(vNum);
                vNum.clear();
            }
            vNum.push_back(s.second);
        }
        else { Relevance.push_back(s.first);  vNum.push_back(s.second);
        }
        f = s.first;
        Iterator++;
    }

    Num.push_back(vNum);
    for (int j = Relevance.size() - 1; j > -1; j--)
    {
        for(size_t i = 0; i < Num[j].size(); i++)
        {
            RelativeIndex RI;
            RI.doc_id = Num[j][i];
            RI.rank = Relevance[j];
            vRI.push_back(RI);
        }
    }
    return vRI;
};

void SearchServer::setMaxResponses(int maxResponse) {
    this->maxResponse = maxResponse;
}
std::vector<std::vector<RelativeIndex>> SearchServer::search(const
                                                             std::vector<std::string>& queries_input)
{
    std::vector<std::vector<std::string>> VecWords;
    std::vector<std::vector<RelativeIndex>> WordsRelative;
    for (int i = 0, is = queries_input.size(); i < is; i++)
    {
        std::istringstream iss(queries_input[i]);
        VecWords.emplace_back(std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}});
    };
    for (int i = 0, is = VecWords.size(); i < is; i++)
    {
        std::vector<RelativeIndex> RelWord(maxResponse);
        std::unordered_map<size_t, float> relativeMap;
        float min = 0;
        for (auto& element : VecWords[i]) {
            for (auto& entry : _index.GetWordCount(element)) {
                relativeMap[entry.doc_id] += entry.count;
            }
        }
        if (relativeMap.empty())
        {
            RelWord.clear();
            WordsRelative.push_back(RelWord);
            continue;
        }
        for (auto&& element : relativeMap) {
            if (element.second > min) {
                RelativeIndex relativeIndex = { element.first, element.second };

                for (size_t j = 0, js = RelWord.size(); j != js; ++j) {
                    if (element.second > RelWord[j].rank) {
                        RelWord.insert(RelWord.begin() + j, relativeIndex);
                        break;
                    }
                }
                RelWord.pop_back();
                min = RelWord.back().rank;
            }
        }
        float max = RelWord[0].rank;
        for (auto&& element : RelWord) {
            element.rank /= max;
            std::stringstream ss;
            ss << std::setprecision(3) << element.rank;
            ss >> element.rank;
        }
        WordsRelative.push_back(RelWord);
    }
    for (auto &w : WordsRelative)
    {
        for(int i = 0 ; i < w.size();)
        {
            if (w[i].rank > 0)
            {
                i++;
            }
            else
            {
                w.erase(w.begin() + i);
            }
        }
    }
    return WordsRelative;
};