#include "dictionary.hpp"

#include <algorithm>
#include <exception>
#include <istream>
#include <fstream>

#include <iostream>
const std::unordered_map<char, int> Dictionary::letter2index{
	{'A', 0},
	{ 'B', 1 },
	{ 'C', 2 },
	{ 'D', 3 },
	{ 'E', 4 },
	{ 'F', 5 },
	{ 'G', 6 },
	{ 'H', 7 },
	{ 'I', 8 },
	{ 'J', 9 },
	{ 'K', 10 },
	{ 'L', 11 },
	{ 'M', 12 },
	{ 'N', 13 },
	{ 'O', 14 },
	{ 'P', 15 },
	{ 'Q', 16 },
	{ 'R', 17 },
	{ 'S', 18 },
	{ 'T', 19 },
	{ 'U', 20 },
	{ 'V', 21 },
	{ 'W', 22 },
	{ 'X', 23 },
	{ 'Y', 24 },
	{ 'Z', 25 } };

class FileNotFound : public std::exception {
public:
	FileNotFound(const std::string& message) : message_(message) {}
	const char* what() const noexcept { return message_.c_str(); }
private:
	std::string message_;
};

void Dictionary::addWord(const std::string& word) {
	if (!dictionaryTree_) dictionaryTree_ = new DictionaryTree;

	DictionaryTree* root = dictionaryTree_;
	for (const auto& letter : word) {

		if (!root->children[letter2index.at(letter)]) {
			root->children[letter2index.at(letter)] = new DictionaryTree;
			root->children[letter2index.at(letter)]->value = letter;
		}

		root = root->children[letter2index.at(letter)];
	}
	root->isWord = true;
}

void Dictionary::readWords(std::istream& istream) {

	std::string word;
	while (std::getline(istream, word)) {
		addWord(word);
	}
}

void Dictionary::readWords(const std::string& filename) {
	std::ifstream ifstream(filename);
	if (!ifstream.is_open()) {
		throw FileNotFound("Could not find file: " + filename);
	}

	readWords(ifstream);
}

Dictionary::Dictionary(const std::string& filename) { readWords(filename); }

Dictionary::Dictionary(std::istream& istream) { readWords(istream); }

//bool Dictionary::isWord(const std::string& word) const {
//	return std::find(words_.begin(), words_.end(), word) != words_.end();
//}

void getWordsRecursive(const DictionaryTree* tree, std::string stub, std::vector<std::string>& words) {
	if (tree->isWord) {
		words.push_back(stub);
	}
	for (const auto& letter : tree->children) {
		if (letter) {
			getWordsRecursive(letter, stub + letter->value, words);
		}
	}
}

std::vector<std::string> Dictionary::getWords() const {
	std::vector<std::string> words;
	getWordsRecursive(dictionaryTree_, "", words);
	return words;
}





