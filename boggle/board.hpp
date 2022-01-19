#pragma once

#include <cstddef>
#include <stdexcept>

class Board {
public:
	Board();
	void generateRandom(const std::size_t& boardSideSize);
	inline std::size_t getSideSize() const { return boardSideSize_; }
	char operator()(const std::size_t x, const std::size_t y) const;
	void setBoard(const std::string& board);
	void print() const;
private:
	std::string board_;
	std::size_t boardSideSize_;
	static const std::string alphabet_;
	static const std::size_t minBoardSideSize_;

	void setBoardSideSize(const std::size_t& boardSideSize);
	
};
