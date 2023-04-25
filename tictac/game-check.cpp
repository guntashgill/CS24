#include <iostream>
#include <string>
#include "Board.h"
#include "Errors.h"

int main() {
  Board board;
  std::string input;

  while (std::getline(std::cin, input)) {
    try {
      Move move(input); 
      board.applyMove(move);

      if (board.isGameOver()) { // Check if the game is over
        if (board.checkWin(Player::X)) {
          std::cout << "Game over: X wins." << std::endl;
          return 0; // Return 0 to indicate successful completion
        } else if (board.checkWin(Player::O)) {
          std::cout << "Game over: O wins." << std::endl;
          return 0; // Return 0 to indicate successful completion
        } else if (board.isDraw()) {
          std::cout << "Game over: Draw." << std::endl;
          return 0; // Return 0 to indicate successful completion
        }
      } else {
        std::cout << "Game in progress: ";
        if (board.getCurrentPlayer() == Player::X) {
          std::cout << "X's turn." << std::endl;
        } else {
          std::cout << "O's turn." << std::endl;
        }
      }
    } catch (const ParseError& e) {
      std::cout << "Parse error." << std::endl; 
      return 1; // Return 1 to indicate a parse error
    } catch (const InvalidMove& e) {
      std::cout << "Invalid move." << std::endl; 
      return 2; // Return 2 to indicate an invalid move
    }
  }

  if (!board.isGameOver()) {
    std::cout << "Game in progress: New game." << std::endl; // Print New game
  }

  return 0; // Exit with status code 0
}


