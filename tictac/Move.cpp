#include "Errors.h"
#include "Move.h"

#include <iostream>
#include <sstream>

Move::Move() {
    number = 0;
    player = ' ';
    row = 0;
    column = 0;
}

Move::Move(const std::string& input) {
    std::istringstream iss(input);

    std::string moveNumber;
    iss >> moveNumber;
    number = std::stoi(moveNumber);

    std::string playerCode;
    iss >> playerCode;
    player = std::toupper(playerCode[0]);

    std::string squareCode;
    iss >> squareCode;
    row = std::toupper(squareCode[0]) - 'A' + 1;
    column = squareCode[1] - '1' + 1;

    std::string comment;
    std::getline(iss >> std::ws, comment);
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
    stream << move.number << ' ' << move.player << ' ' << static_cast<char>(move.row - 1 + 'A') << move.column - 1 + '1';
    return stream;
}



