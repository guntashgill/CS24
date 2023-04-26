#include <iostream>
#include <string>
#include "Board.h"
#include "Errors.h"

int main() {
  Board board;
  std::string input;
  int moves = 0; 
  int row;
  int column;

  while (std::getline(std::cin, input)){
    if (!board.isGameOver()) {
      
      if (board.getCurrentPlayer() == O) {
        std::cout << "O's turn." << std::endl;
        return 0;
      if ( board.getCurrentPlayer() == X) {
        std::cout << "X's turn." << std::endl;
        return 0;
      }
      std::cout << "Game in progress: ";
    }
    if (board.isGameOver()) {
      if (board.checkWin(Player::X)) {
        std::cout << "Game over: X wins." << std::endl;
      }
      if (board.checkWin(Player::O)) {
        std::cout << "Game over: O wins" << std::endl;
      }
    }
    if (board.isDraw()) {
      std::cout << "Game over: Draw" << std::endl;
    }

  }

  }
}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
//   while (std::getline(std::cin, input)) {
//     try {
//       if (input.empty() && moves == 0){
//         break;
//       }
//       moves++; 
//       Move move(input); 
//       board.applyMove(move);

//       if (board.isGameOver()) {
//         if (board.checkWin(Player::X)) {
//           std::cout << "Game over: X wins." << std::endl;
//         } else if (board.checkWin(Player::O)) {
//           std::cout << "Game over: O wins." << std::endl;
//         } else if (board.isDraw()) {
//           std::cout << "Game over: Draw." << std::endl;
//         }
//         return 0;
//       } else {
//         std::cout << "Game in progress: ";
//         if (board.getCurrentPlayer() == X) {
//           std::cout << "X's turn." << std::endl;
//           return 0;
//         } else {
//           std::cout << "O's turn." << std::endl;
//           return 0;
//         }
//       }
//     } catch (const ParseError& e) {
//       std::cout << "Parse error." << std::endl; 
//       return 1; 
//     } catch (const InvalidMove& e) {
//       std::cout << "Invalid move." << std::endl; 
//       return 2; 
//     } 
//   }

//   if (!board.isGameOver()) {
//     std::cout << "Game in progress: New game." << std::endl;
//   }

//   return 0;
// }





