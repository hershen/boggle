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

	void setBoard(const std::string& string) {
		if (string.size() != boardSideSize_ * boardSideSize_) {
			std::cout << "Wrong string length\n";
			return;
		}
		for (int i = 0; i < string.size(); ++i) { board_[i].value = string[i]; }
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
const std::string Board::alphabet_{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::size_t Board::minBoardSideSize_{ 3 };


class Game
{
public:
	Game(const Dictionary& dictionary) :dictionary_(dictionary) {}

	std::vector<std::string> findWords(Board& board) {
		std::vector<std::string> validWords;
		for (int row = 0; row < board.getSideSize(); ++row) {
			for (int column = 0; column < board.getSideSize(); ++column) {
				findWordsRecursive(&board(row, column), "", dictionary_.getTree(), validWords);
			}
		}
		return validWords;
	}

private:
	void findWordsRecursive(Letter* letter, std::string stub, const DictionaryTree* dictionaryTree, std::vector<std::string>& validWords) {
		if (!letter or !letter->valid) { return; }
		const auto childTree = dictionaryTree->children[Dictionary::letter2index.at(letter->value)];
		if (!childTree) { return; }


		stub += letter->value;

		letter->valid = false;
		if (childTree->isWord) { validWords.push_back(stub); }
		findWordsRecursive(letter->upperLeft, stub, childTree, validWords);
		findWordsRecursive(letter->up, stub, childTree, validWords);
		findWordsRecursive(letter->upperRight, stub, childTree, validWords);
		findWordsRecursive(letter->right, stub, childTree, validWords);
		findWordsRecursive(letter->lowerRight, stub, childTree, validWords);
		findWordsRecursive(letter->down, stub, childTree, validWords);
		findWordsRecursive(letter->lowerLeft, stub, childTree, validWords);
		findWordsRecursive(letter->left, stub, childTree, validWords);
		letter->valid = true;
	}
	std::vector<std::string> words_;
	Dictionary dictionary_;
};

int main() {
	std::srand(static_cast<unsigned int>(std::time(0)));

	Board board(3);
	board.generateRandom();
	board.setBoard("BOBAAAAAA");
	board.print();

	Dictionary dictionary("dictionary.txt");

	const auto& dictWords = dictionary.getWords();
	std::cout << "Dictionary has " << dictWords.size() << ". Words are: \n";
	for (const auto& word : dictWords) {
		std::cout << word << "\n";
	};


	Game game(dictionary);
	const auto foundWords = game.findWords(board);
	std::cout << "\nfound words:\n";
	for (const auto& word : foundWords) {
		std::cout << word << std::endl;
	}
}
