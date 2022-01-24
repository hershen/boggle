#include "Game.h"

Game::findWordsRecursive(board, row, column);

Output Game::findWords(const Board& board) {
	words_.clear();
	for (int row = 0; row < board.getSideSize(); ++row) {
		for (int column = 0; column < board.getSideSize(); ++column) {
			findWordsRecursive(board, row, column);
		}
	}
}