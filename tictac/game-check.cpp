#include "Move.h"
#include "Errors.h"
#include "Board.h"
#include <iostream>
#include <string>

int main() {
  Board board;
  std::string input;
  bool validMoves = true;

  while (std::getline(std::cin, input)) {
    try {
      Move move(input);
      board.gameMove(move);
    } catch (const ParseError& error) {
      std::cerr << "Parse error." << std::endl;
      return 1;
    } catch (const InvalidMove& error) {
      std::cerr << "Invalid move." << std::endl;
      return 2;
    }
  }

  board.gameResult();
  return 0;
}

