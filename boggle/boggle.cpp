#include <ctime>


//#include "board.hpp"
#include "dictionary.hpp"
//#include "output.hpp"

struct Letter {
	Letter* upperLeft = nullptr;
	Letter* up = nullptr;
	Letter* upperRight = nullptr;
	Letter* right = nullptr;
	Letter* lowerRight = nullptr;
	Letter* down = nullptr;
	Letter* lowerLeft = nullptr;
	Letter* left = nullptr;
	char value = ' ';
	bool valid = true;
};

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
class Board {
public:
	Board(const int boardSideSize) : boardSideSize_(boardSideSize) {
		if (boardSideSize < minBoardSideSize_) {
			throw std::domain_error("Board side size needs to be at least " + std::to_string(minBoardSideSize_));
		}

		board_.resize(boardSideSize_ * boardSideSize_);

		for (int row = 0; row < boardSideSize_; ++row) {
			for (int column = 0; column < boardSideSize_; ++column) {
				Letter& letter = (*this)(row, column);

				if (row > 0) {
					letter.up = &(*this)(row - 1, column);
					if (column > 0) {
						letter.upperLeft = &(*this)(row - 1, column - 1);
					}
					if (column < boardSideSize_ - 1) {
						letter.upperRight = &(*this)(row - 1, column + 1);
					}
				}
				if (row < boardSideSize_ - 1) {
					letter.down = &(*this)(row + 1, column);
					if (column > 0) {
						letter.lowerLeft = &(*this)(row + 1, column - 1);
					}
					if (column < boardSideSize_ - 1) {
						letter.lowerRight = &(*this)(row + 1, column + 1);
					}
				}
				if (column > 0) {
					letter.left = &(*this)(row, column - 1);
				}
				if (column < boardSideSize_ - 1) {
					letter.right = &(*this)(row, column + 1);
				}
			}
		}
	}

	inline int getSideSize() const { return boardSideSize_; }

	void generateRandom() {
		for (int row = 0; row < boardSideSize_; ++row) {
			for (int column = 0; column < boardSideSize_; ++column) {
				(*this)(row, column).value = alphabet_[static_cast<int>(static_cast<double>(std::rand()) / RAND_MAX * alphabet_.size())];
			}
		}
	}


	Letter& operator()(const int x, const int y) {
		return board_[x * boardSideSize_ + y];
	}

	void print() const {
		std::cout << "The board is:\n";
		for (int i = 0; i < boardSideSize_ * boardSideSize_; ++i) {
			std::cout << board_[i].value;
			if (i % boardSideSize_ == boardSideSize_ - 1) {
				std::cout << "\n";
			}
		}
		std::cout << "\n";
	}
private:
	std::vector<Letter> board_;
	int boardSideSize_;
	static const std::string alphabet_;
	static const std::size_t minBoardSideSize_;
};
const std::string Board::alphabet_ = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::size_t Board::minBoardSideSize_ = 3;


class Game
{
public:
	Game(const Dictionary& dictionary) :dictionary_(dictionary) {}

	void findWords(const Board& board) {

		std::vector<std::string> validRestOfWords = dictionary_.getWords();

		for (int row = 0; row < board.getSideSize(); ++row) {
			for (int column = 0; column < board.getSideSize(); ++column) {
				findWordsRecursive(board, row, column, "", validRestOfWords);
			}
		}
	}

private:
	void findWordsRecursive(
		const Board& board,
		const int currentRow,
		const int currentColumn,
		std::string currentLetterSequence,
		std::vector<std::string>& validRestOfWords) {

		std::vector<std::string> newValidRestOfWords;

		for (const auto& word : validRestOfWords) {
			if (word.size() == 0) {
				words_.push_back(currentLetterSequence);
			}

			else if (word[0] == board(currentRow, currentColumn)) {
				newValidRestOfWords.push_back(word.substr(1, std::string::npos));
			}
		}

		for (up, down, left, right, diagonals) {
			findWordsRecursive(
				board,
				currentRow,
				currentColumn,
				currentLetterSequence + board(currentRow, currentColumn),
				validRestOfWords);
		}
	}
	std::vector<std::string> words_;
	Dictionary dictionary_;
};

int main() {
	std::srand(static_cast<unsigned int>(std::time(0)));

	Board board(4);
	board.generateRandom();
	board.print();

	Dictionary dictionary("dictionary.txt");




	//Game game(dictionary);
	//game.findWords(board);
	/* game.getFoundWords().print(); */
}
