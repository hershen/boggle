#include "pch.h"

#include "../boggle/board.hpp"

TEST(testBoard, testDefaultBoardSize) {
	Board board;

	EXPECT_GE(board.getSideSize(), 3) << "Minimum board size is 3";
}

TEST(testBoard, testGenerateBoardSize) {
	Board board;
	board.generateRandom(6);

	EXPECT_EQ(board.getSideSize(), 6);
}

TEST(testBoard, testElementAccess) {
	Board board;
	const std::string boardString = "ABCDEFGHI";
	board.setBoard(boardString);
	for (std::size_t i = 0; i < boardString.size(); ++i) {
		const auto x = static_cast<std::size_t>(i / board.getSideSize());
		const auto y = static_cast<std::size_t>(i % board.getSideSize());
		EXPECT_EQ(board(x, y), boardString[i]);
	}
}
