#include "pch.h"

#include "../boggle/dictionary.hpp"

#include <algorithm>
#include <sstream>

class DictionaryTest : public ::testing::Test {
protected:
	std::vector<std::string> realWords{ "HEY", "BLUE", "STORM" };
};

TEST_F(DictionaryTest, constructorFilename) {
	Dictionary dictionary("../../tests/testDictionary.txt");

	for (const auto& word : realWords) {
		EXPECT_TRUE(dictionary.isWord(word)) << word << " is supposed to be a real word, but isn't";
	}
	EXPECT_FALSE(dictionary.isWord("NOTWORD"));
}
TEST_F(DictionaryTest, constructorIstream) {

	std::stringstream stringstream;
	std::for_each(realWords.begin(), realWords.end(), [&stringstream](const auto& word) {stringstream << word << "\n"; });
	std::istream istream(stringstream.rdbuf());

	Dictionary dictionary(istream);

	for (const auto& word : realWords) {
		EXPECT_TRUE(dictionary.isWord(word));
	}
	EXPECT_FALSE(dictionary.isWord("NOTWORD"));
}
TEST_F(DictionaryTest, isWord) {
	Dictionary dictionary(realWords);

	for (const auto& word : realWords) {
		EXPECT_TRUE(dictionary.isWord(word));
	}
	EXPECT_FALSE(dictionary.isWord("NOTWORD"));
}


