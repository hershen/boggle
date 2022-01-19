#include "dictionary.hpp"

#include <algorithm>
#include <exception>
#include <istream>
#include <fstream>

class FileNotFound : public std::exception {
public:
	FileNotFound(const std::string& message) : message_(message) {}
	const char* what() const noexcept { return message_.c_str(); }
private:
	std::string message_;
};

std::vector<std::string> readWords(std::istream& istream) {

	std::vector<std::string> words;
	std::string word;
	while (std::getline(istream, word)) {
		words.push_back(word);
	}
	return words;
}

std::vector<std::string> readWords(const std::string& filename) {
	std::ifstream ifstream(filename);
	if (!ifstream.is_open()) {
		throw FileNotFound("Could not find file: " + filename);
	}

	return readWords(ifstream);
}

Dictionary::Dictionary(const std::string& filename) : words_(readWords(filename)) {}

Dictionary::Dictionary(std::istream& istream) : words_(readWords(istream)) {}

Dictionary::Dictionary(std::vector<std::string> words) : words_(words) {}

bool Dictionary::isWord(const std::string& word) const {
	return std::find(words_.begin(), words_.end(), word) != words_.end();
}




