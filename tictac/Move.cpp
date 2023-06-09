#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Move::Move() {
    number = 0;
    player = ' ';
    row = 0;
    column = 0;
}

Move::Move(const std::string& input) {
    std::istringstream iss(input);

    std::string moveNumber;
    if (!(iss >> moveNumber)) {
        throw ParseError("Invalid move number format");
    }

    try {
        number = std::stoi(moveNumber);
        if (number < 1 || number > 9) {
            throw ParseError("Invalid move number above 1 or 9");
        }
    } catch (const std::invalid_argument&) {
        throw ParseError("Invalid move number");
    }

    std::string afterMoveNumber;
    if (!(iss >> afterMoveNumber)) {
        throw ParseError("Invalid player");
    }
    if (afterMoveNumber.length() != 1 || (afterMoveNumber[0] != 'X' && afterMoveNumber[0] != 'O')) {
        throw ParseError("Invalid player");
    }
    player = std::toupper(afterMoveNumber[0]);

    std::string afterPlayer;
    if (!(iss >> afterPlayer)) {
        throw ParseError("Invalid row or column");
    }

    if (afterPlayer.length() != 2) {
        throw ParseError("Invalid row or column");
    }

    row = static_cast<int>(std::toupper(afterPlayer[0])) - 'A' + 1;
    column = afterPlayer[1] - '0';

    if (row < 1 || row > 3 || column < 1 || column > 3) {
        throw ParseError("Invalid row or column");
    }

    std::string afterMove;
    if (iss >> afterMove && afterMove[0] != '#') {
        throw ParseError("Invalid move");
    }
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
    stream << move.number << ' ' << move.player << ' ' << static_cast<char>(move.row - 1 + 'A') << move.column;
    return stream;
}



