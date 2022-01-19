#include "board.hpp"

#include <cmath>
#include <cstdlib>
#include <string>


#include <iostream>

const std::string Board::alphabet_ = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::size_t Board::minBoardSideSize_ = 3;

Board::Board() : boardSideSize_(minBoardSideSize_) {}

void Board::generateRandom(const std::size_t& boardSideSize) {
	setBoardSideSize(boardSideSize);
	board_.resize(boardSideSize_ * boardSideSize_);

	for (int i = 0; i < boardSideSize_ * boardSideSize_; ++i) {
		board_[i] = alphabet_[static_cast<int>(static_cast<double>(std::rand()) / RAND_MAX * alphabet_.size())];
	}
}

char Board::operator()(const std::size_t x, const std::size_t y) const {
	return board_[x * boardSideSize_ + y];
}

void Board::setBoard(const std::string& board) {
	this->setBoardSideSize(static_cast<std::size_t>(std::sqrt(board.size())));
	board_ = board;
}


void Board::print() const {
	std::cout << "The board is:\n";
	for (int i = 0; i < boardSideSize_ * boardSideSize_; ++i) {
		std::cout << board_[i];
		if (i % boardSideSize_ == boardSideSize_ - 1) {
			std::cout << "\n";
		}
	}
	std::cout << "\n";
}

void Board::setBoardSideSize(const std::size_t& boardSideSize) {
	if (boardSideSize < minBoardSideSize_) {
		throw std::domain_error("Board size needs to be at least 3");
	}

	boardSideSize_ = boardSideSize;
}
