#include "pch.h"

#include "../boggle/output.hpp"

TEST(testOutput, testEmptyAtStartup) {
	Output output;
	EXPECT_TRUE(output.getWords().empty());
}

TEST(testOutput, testAddingWords) {
	Output output;
	std::vector<std::string> words{ "HEY", "THERE", "FRIEND" };
	for (const auto& word : words) {
		output.addWord(word);
	}
	EXPECT_EQ(output.getWords().size(), words.size());
	for (int i = 0; i < words.size(); ++i) {
		EXPECT_EQ(output.getWords()[i], words[i]);
	}
}