#include "Errors.h"
#include "Move.h"
#include <cctype>

Move::Move(const std::string& input) {
    size_t pos = 0;

    // Parse move number
    number = std::stoi(input, &pos);
    if (number < 1 || number > 9 || pos == 0 || input[pos] != ' ') {
        throw InvalidMove("Invalid move: " + input);
    }

    // Skip whitespace
    pos++;

    // Parse player code
    player = input[pos++];
    if (player != 'X' && player != 'O' && player != 'x' && player != 'o') {
        throw InvalidMove("Invalid move: " + input);
    }
    player = std::toupper(player);

    // Skip whitespace
    pos++;

    // Parse square code
    if (pos + 1 >= input.size() || !std::isalpha(input[pos]) || !std::isdigit(input[pos + 1])) {
        throw InvalidMove("Invalid move: " + input);
    }
    row = input[pos++] - 'A' + 1; // Convert row letter to corresponding integer (A=1, B=2, C=3)
    column = input[pos++] - '0'; // Convert column digit to integer

    // Skip optional whitespace
    while (pos < input.size() && std::isspace(input[pos])) {
        pos++;
    }

    // Check for optional comment
    if (pos < input.size() && input[pos] == '#') {
        // Comment found, skip to end of line
        pos = input.size();
    }

    // If there are any characters left, it's not a valid move
    if (pos != input.size()) {
        throw InvalidMove("Invalid move: " + input);
    }
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
    stream << move.number << " " << move.player << " ";
    char rowLetter = move.row + 'A' - 1; // Convert row integer to corresponding letter (1=A, 2=B, 3=C)
    stream << rowLetter << move.column;
    return stream;
}


