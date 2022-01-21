#pragma once

#include <string>
#include <vector>

class Dictionary {
public:
	explicit Dictionary(const std::string& filename);
	explicit Dictionary(std::istream& istream);

	bool isWord(const std::string& word) const;

private:
	std::vector<std::string> words_;
};