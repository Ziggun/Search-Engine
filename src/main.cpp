#include "SearchServer.h"

int main()
{
    setlocale(LC_ALL, "ru");
    InvertedIndex invertIndex;
    ConverterJSON converterJSON;

    invertIndex.UpdateDocumentBase(converterJSON.GetTextDocuments());
    std::vector<string> SearchWords = converterJSON.GetRequests();

    SearchServer searchServer(invertIndex);
    searchServer.setMaxResponses(converterJSON.GetResponsesLimit());

    auto vRelativeIndex = searchServer.search(SearchWords);
    std::vector<std::vector<std::pair<int, float>>> Result;
    size_t count = 0;
    for (int i = 0, im = vRelativeIndex.size(); i < im; i++)
    {
        Result.emplace_back();
        for (auto a : vRelativeIndex[i])
        {
            Result[i].push_back({ static_cast<int>(a.doc_id),a.rank });
            count++;
        }
    }
    converterJSON.putAnswers(Result);
    std::cout << "Searching finished. Put answers: " << count << "!" << std::endl;
    return 0;
}