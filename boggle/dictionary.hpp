#pragma once

#include <array>
#include <string>
#include <vector>
#include <unordered_map>



struct DictionaryTree {
	std::array<DictionaryTree*, 26> children{nullptr};
	char val = ' ';
	bool isWord = false;
};

class Dictionary {
public:
	explicit Dictionary(const std::string& filename);
	explicit Dictionary(std::istream& istream);

	//bool isWord(const std::string& word) const;
	std::vector<std::string> getWords() const;

	static const std::unordered_map<char, int> letter2index;

private:
	DictionaryTree* dictionaryTree_;
	void addWord(const std::string& word);
	void readWords(std::istream& istream);
	void readWords(const std::string& filename);
};