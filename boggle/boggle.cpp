#include <ctime>

#include "board.hpp"
#include "dictionary.hpp"


#include <iostream>

int main() {
	std::srand(static_cast<unsigned int>(std::time(0)));

	Board board;
	board.generateRandom(4);
	board.print();

	Dictionary dictionary("dictionary.txt");
	std::cout << "Dictionary has " << dictionary.getWords().size() << " words.\n";

	/* Game game; */
	/* game.play(input); */
	/* game.print(); */
}
