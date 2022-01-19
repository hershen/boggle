#include "pch.h"

#include "../boggle/dictionary.hpp"

TEST(testDictionary, testgetWords) {
	const std::vector<std::string> words{ "HEY", "BLUE", "STORM" };
	Dictionary dictionary(words);
	EXPECT_EQ(dictionary.getWords().size(), 3);
	for (int i = 0; i < words.size(); ++i) {
		EXPECT_EQ(dictionary.getWords()[i], words[i]);
	}
}
TEST(testDictionary, testisRealWord) {
	const std::vector<std::string> realWords{ "HEY", "BLUE", "STORM" };
	Dictionary dictionary(realWords);

	for (const auto& word : realWords) {
		EXPECT_TRUE(dictionary.isRealWord(word));
	}
	EXPECT_FALSE(dictionary.isRealWord("NOTWORD"));
}
