#include "Errors.h"
#include "Move.h"
#include <string> 
#include <vector>
#include <iostream>
#include <sstream>

// Space for implementing Move functions.

Move::Move() {
    number = 0;
    player = ' ';
    row = 0;
    column = 0;
}

Move::Move(const std::string& input) {
    std::istringstream iss(input);

    std::string moveInfo;
    iss >> moveInfo;

    size_t numberPos = moveInfo.find("number");
    size_t playerPos = moveInfo.find("player");
    size_t rowPos = moveInfo.find("row");
    size_t columnPos = moveInfo.find("column");

    if (numberPos == std::string::npos || playerPos == std::string::npos ||
        rowPos == std::string::npos || columnPos == std::string::npos) {
        throw ParseError("Invalid move format");
    }

    try {
        std::string numberStr = moveInfo.substr(numberPos + 6, playerPos - numberPos - 7);
        number = std::stoi(numberStr);
        if (number < 1 || number > 9) {
            throw ParseError("Invalid move number (should be between 1 and 9)");
        }

        std::string playerStr = moveInfo.substr(playerPos + 6, rowPos - playerPos - 7);
        if (playerStr.length() != 1 || (playerStr[0] != 'X' && playerStr[0] != 'O')) {
            throw ParseError("Invalid player");
        }
        player = playerStr[0];

        std::string rowStr = moveInfo.substr(rowPos + 3, columnPos - rowPos - 4);
        row = std::stoi(rowStr);
        if (row < 1 || row > 3) {
            throw ParseError("Invalid row");
        }

        std::string columnStr = moveInfo.substr(columnPos + 6);
        column = std::stoi(columnStr);
        if (column < 1 || column > 3) {
            throw ParseError("Invalid column");
        }
    } catch (std::invalid_argument const&) {
        throw ParseError("Invalid move format");
    }
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
    stream << "MoveInfo: number=" << move.number << " player=" << move.player
           << " row=" << move.row << " column=" << move.column;
    return stream;
}


