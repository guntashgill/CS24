#include "Board.h"
#include "Move.h"
#include <iostream>
#include <sstream>
#include <string>

int main() {
    Board board; // Create an instance of the Board class
    std::string input;

    while (true) {
        if (board.getCurrentPlayer() == 'X') {
            std::cout << "Game in progress: X's turn." << std::endl;
            return 0; // Exit the program with success status code
        } else if (board.getCurrentPlayer() == 'O') {
            std::cout << "Game in progress: O's turn." << std::endl;
            return 0; // Exit the program with success status code
        }

        std::cout << "Enter move (row col): ";
        if (!std::getline(std::cin, input) || input.empty()) {
            // Check for end of file or empty input
            break; // Exit the game loop
        }

        if (input == "quit") {
            break; // Exit the game loop if input is "quit"
        }

        if (input == "new game") {
            std::cout << "Game in progress: New game." << std::endl;
            return 0; // Exit the program with success status code
        }

        int row, col;
        std::istringstream iss(input);
        if (iss >> row >> col) {
            // Validate row and col values
            if (row >= 0 && row < Board::BOARD_SIZE && col >= 0 && col < Board::BOARD_SIZE) {
                // Update the board with the move
                std::string moveString = std::to_string(row) + " " + std::to_string(col);
                Move move(moveString);
                board.applyMove(move);

                // Print the updated board
                std::cout << board << std::endl;

                // Check for game over condition
                if (board.isGameOver()) {
                    if (board.getCurrentPlayer() == 'X') {
                        std::cout << "Game over: X wins!" << std::endl;
                        return 0; // Exit the program with success status code
                    } else if (board.getCurrentPlayer() == 'O') {
                        std::cout << "Game over: O wins!" << std::endl;
                        return 0; // Exit the program with success status code
                    } else if (board.isDraw()) {
                        std::cout << "Game over: Draw!" << std::endl;
                        return 0; // Exit the program with success status code
                    }
                }
            } else {
                std::cout << "Invalid move. Row and col must be within the board size (0-" << (Board::BOARD_SIZE - 1) << "). Try again." << std::endl;
                continue; // Continue to next iteration of the game loop
            }
        } else {
            std::cout << "Invalid input. Try again." << std::endl;
            continue; // Continue to next iteration of the game loop
        }
    }

    return 0; // Exit the program with success status code
}




