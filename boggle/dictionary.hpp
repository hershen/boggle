#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Dictionary {
public:
	Dictionary(const std::string& filename);
	Dictionary(std::vector<std::string> words);

	inline std::vector<std::string> getWords() const { return words_; }

	bool isRealWord(const std::string& word) const;

private:
	std::vector<std::string> words_;

	std::vector<std::string> readFile(const std::string& filename);
};
