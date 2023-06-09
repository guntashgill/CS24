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
    while (std::getline(std::cin, line)) {
        try {
            if (line.empty()) {
                break;
            }

            move = Move(line);
            moveCount++;

            board.gameMove(move);

            if (board.isGameOver()) {
                if (getline(std::cin, line)) {
                    std::cout << "Invalid move." << std::endl;
                    return 2;
                }
                if (board.hasPlayerWon('X')) {
                    std::cout << "Game over: X wins." << std::endl;
                } else if (board.hasPlayerWon('O')) {
                    std::cout << "Game over: O wins." << std::endl;
                } else {
                    std::cout << "Game over: Draw." << std::endl;
                }
                return 0;
            }
        } catch (ParseError const&) {
            std::cout << "Parse error." << std::endl;
            return 1;
        } catch (InvalidMove const&) {
            std::cout << "Invalid move." << std::endl;
            return 2;
        }
    }

    if (moveCount == 0) {
        std::cout << "Game in progress: New game." << std::endl;
    } else {
        std::cout << "Game in progress: ";
        if (board.getPlayerTurn() == 'X') {
            std::cout << "O's turn." << std::endl;
        } else {
            std::cout << "X's turn." << std::endl;
        }
    }

    return 0;
}
