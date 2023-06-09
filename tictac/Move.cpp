#include "Errors.h"
#include "Move.h"
#include <sstream>

Move::Move() : number(0), player(' '), row(0), column(0) {}

Move::Move(const std::string& input) {
    std::istringstream iss(input);

    std::string moveNumber;
    iss >> moveNumber;
    try {
        number = std::stoi(moveNumber);
        if (number < 1 || number > 9)
            throw ParseError("Invalid move number (1-9).");
    } catch (std::invalid_argument const&) {
        throw ParseError("Invalid move number format.");
    }

    std::string playerStr;
    iss >> playerStr;
    if (playerStr.length() != 1 || (playerStr[0] != 'X' && playerStr[0] != 'O' && playerStr[0] != 'x' && playerStr[0] != 'o')) {
        throw ParseError("Invalid player.");
    }
    player = std::toupper(playerStr[0]);

    std::string moveStr;
    iss >> moveStr;
    if (moveStr.length() != 2 || !std::isdigit(moveStr[0]) || !std::isdigit(moveStr[1])) {
        throw ParseError("Invalid row or column.");
    }
    row = moveStr[0] - '0';
    column = moveStr[1] - '0';
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
    stream << move.number << ' ' << move.player << ' ' << move.row << move.column;
    return stream;
}



