#include "Board.h"
#include "Errors.h"
#include "Move.h"

#include <iostream>
#include <string>

int main() {
    Board board;
    Move move;
    int moveCount = 0;

    std::string line;
    while (getline(std::cin, line)) {
        try {
            if (line.empty()) {
                break;
            }

            move = Move(line);
            moveCount++;

        } catch (ParseError const&) {
            std::cout << "Parse error." << std::endl;
            return 1;
        }
        try {
            board.applyMove(move);
        } catch (InvalidMove const&) {
            std::cout << "Invalid move." << std::endl;
            return 2;
        }

        if (board.isGameOver()) {
            if (getline(std::cin, line)) {
                std::cout << "Invalid move." << std::endl;
                return 2;
            }
            if (board.getCurrentPlayer() == 'X') {
                std::cout << "Game over: O wins." << std::endl;
            } else {
                std::cout << "Game over: X wins." << std::endl;
            }
            return 0;
        }
    }

    if (moveCount == 0) {
        std::cout << "Game in progress: New game." << std::endl;
    } else {
        std::cout << "Game in progress: ";
        if (board.getCurrentPlayer() == 'X') {
            std::cout << "O's turn." << std::endl;
        } else {
            std::cout << "X's turn." << std::endl;
        }
    }
    return 0;
}
