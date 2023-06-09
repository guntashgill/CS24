#include "Board.h"
#include "Errors.h"
#include "Move.h"

#include <iostream>
#include <string>

int main() {
  Board board;
  std::string line;
  int moveCount = 0;

  while (std::getline(std::cin, line)) {
    try {
      Move move(line);
      moveCount++;

      if (moveCount % 2 == 1 && move.player != 'X') {
        throw InvalidMove("Invalid player for the current move.");
      }

      if (moveCount % 2 == 0 && move.player != 'O') {
        throw InvalidMove("Invalid player for the current move.");
      }

      board.applyMove(move);

      if (board.isGameOver()) {
        if (board.hasPlayerWon('X')) {
          std::cout << "Game over: X wins.\n";
        } else if (board.hasPlayerWon('O')) {
          std::cout << "Game over: O wins.\n";
        } else {
          std::cout << "Game over: Draw.\n";
        }
        return 0;
      } else {
        if (board.isDraw()) {
          std::cout << "Game over: Draw.\n";
          return 0;
        } else {
          if (moveCount % 2 == 1) {
            std::cout << "Game in progress: O's turn.\n";
          } else {
            std::cout << "Game in progress: X's turn.\n";
          }
        }
      }
    } catch (const ParseError& e) {
      std::cout << "Parse error: " << e.what() << '\n';
      return 1;
    } catch (const InvalidMove& e) {
      std::cout << "Invalid move: " << e.what() << '\n';
      return 2;
    }
  }

  if (moveCount == 0) {
    std::cout << "Game in progress: New game.\n";
  } else if (moveCount % 2 == 1) {
    std::cout << "Game in progress: O's turn.\n";
  } else {
    std::cout << "Game in progress: X's turn.\n";
  }

  return 0;
}





