#include "InvertedIndex.h"

void ThreadFile(std::map<std::string, std::vector<Entry>>& freq_dictionary, const string& textStrings, const int& number)
{
    std::stringstream ss(textStrings);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vStrings(begin, end);
    for (int j = 0,  jm = vStrings.size(); j < jm; j++)
    {
        auto FreqDict = freq_dictionary.find(vStrings[j]);
        if (FreqDict == freq_dictionary.end())
        {
            std::vector<Entry> VEntry;
            Entry entry;
            entry.doc_id = number;
            entry.count = 1;
            VEntry.push_back(entry);
            freq_dictionary.emplace(vStrings[j], VEntry);
            FreqDict = freq_dictionary.find(vStrings[j]);
        } else
        {
            bool b = false;
            for (int k = 0, km = FreqDict->second.size(); k < km; k++)
            {
                if (FreqDict->second[k].doc_id == number)
                {
                    b = true;
                    FreqDict->second[k].count++;
                }
            }
            if (!b)
            {
                Entry entry;
                entry.doc_id = number;
                entry.count = 1;
                FreqDict->second.push_back(entry);
            }
        }
    }
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    for (int i = 0, im = input_docs.size(); i < im; i++)
    {
        thread thd(ThreadFile, ref(freq_dictionary), input_docs[i], i);
        thd.join();
    }
};

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> result{};
    auto it = freq_dictionary.find(word);
    if (it == freq_dictionary.end())
        return result;
    for (auto e : it->second)
        result.push_back(e);
    return result;
};