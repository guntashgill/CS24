#include <iostream>
#include "Board.h"
#include "Errors.h"
#include "Move.h"

int main() {
  Board board;

  Player currentPlayer = Player::X;

  while (!board.isGameOver()) {
    std::cout << "Current Board:" << std::endl;
    std::cout << board << std::endl;

    int row, col;
    std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << "'s turn" << std::endl;
    std::cout << "Enter row (0-2): ";
    std::cin >> row;
    std::cout << "Enter column (0-2): ";
    std::cin >> col;
    std::string input = std::to_string(row) + " " + std::to_string(col) + " " + (currentPlayer == Player::X ? "X" : "O");
    Move move(input);
    try {
     board.applyMove(move);

      if (board.checkWin(currentPlayer)) {
        std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << " wins!" << std::endl;
        break;
      }

      if (board.isDraw()) {
        std::cout << "It's a draw!" << std::endl;
        break;
      }

      currentPlayer = (currentPlayer == Player::X ? Player::O : Player::X);

    } catch (const InvalidMove& e) {
      std::cout << "Invalid move. Please try again." << std::endl;
    }
  }

  std::cout << "Final Board:" << std::endl;
  std::cout << board << std::endl;

  return 0;
}

 

