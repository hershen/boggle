#pragma once

#include <string>
#include <vector>

class Dictionary {
public:
	explicit Dictionary(const std::string& filename);
	explicit Dictionary(std::istream& istream);

	bool isWord(const std::string& word) const;
	inline std::vector<std::string> getWords() const { return words_; }

private:
	std::vector<std::string> words_;
};