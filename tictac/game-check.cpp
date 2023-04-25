#include <iostream>
#include <string>
#include "Board.h"
#include "Errors.h"

int main() {
  Board board; // Create an instance of the Board class
  std::string input; // String to store input

  while (std::getline(std::cin, input)) { // Read input from standard input
    try {
      Move move(input); // Parse input as a Move object
      board.applyMove(move); // Apply move to the board

      if (board.isGameOver()) { // Check if the game is over
        if (board.checkWin(Player::X)) {
          std::cout << "Game over: X wins." << std::endl; // Print X wins
        } else if (board.checkWin(Player::O)) {
          std::cout << "Game over: O wins." << std::endl; // Print O wins
        } else if (board.isDraw()) {
          std::cout << "Game over: Draw." << std::endl; // Print Draw
        }
        return 0; // Exit with status code 0
      } else {
        // Print whose turn it is
        std::cout << "Game in progress: " << (board.getCurrentPlayer() == Player::X ? "X's turn." : "O's turn.") << std::endl;
      }
    } catch (const ParseError& e) {
      std::cout << "Parse error." << std::endl; // Print Parse error
      return 1; // Exit with status code 1
    } catch (const InvalidMove& e) {
      std::cout << "Invalid move." << std::endl; // Print Invalid move
      return 2; // Exit with status code 2
    }
  }

  // Print game result if end of input is reached
  if (!board.isGameOver()) {
    std::cout << "Game in progress: New game." << std::endl; // Print New game
  }

  return 0; // Exit with status code 0
}

