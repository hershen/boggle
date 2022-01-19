#pragma once

#include <string>
#include <vector>

class Output
{
public:
	void addWord(const std::string& word);
	inline std::vector<std::string> getWords() { return words_; }
	void print() const;
private:
	std::vector<std::string> words_;
};

