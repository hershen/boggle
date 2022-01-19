#include "dictionary.hpp"

#include <algorithm>
#include <exception>
#include <fstream>

class FileNotFound : public std::exception {
public:
	FileNotFound(const std::string& message) : message_(message) {}
	const char* what() const noexcept { return message_.c_str(); }
private:
	std::string message_;
};

Dictionary::Dictionary(const std::string& filename) : words_(readFile(filename)) {}

Dictionary::Dictionary(std::vector<std::string> words) : words_(words) {}

bool Dictionary::isRealWord(const std::string& word) const {
	return std::find(words_.begin(), words_.end(), word) != words_.end();
}

std::vector<std::string> Dictionary::readFile(const std::string& filename) {
	std::ifstream fstream(filename);
	if (!fstream.is_open()) {
		throw FileNotFound(filename);
	}

	std::vector<std::string> words;
	std::string word;
	while (fstream >> word) {
		words.push_back(word);
	}
	return words;
}


