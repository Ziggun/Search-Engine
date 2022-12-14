#pragma once
#include "InvertedIndex.h"

struct RelativeIndex {
	size_t doc_id;
	float rank;
	bool operator ==(const RelativeIndex& other) const {
		return (doc_id == other.doc_id && rank == other.rank);
	}
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) { };
    std::vector<std::vector<RelativeIndex>> search(const
        std::vector<std::string>& queries_input) const;
    std::vector <RelativeIndex> uniqueWords(multimap<float, int> sR) const;
    void setMaxResponses(int maxResponse);

private:
	InvertedIndex _index;
	int maxResponse = 5;
};