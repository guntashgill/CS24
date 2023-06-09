#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <sstream>
#include <cctype>

Move::Move() : number(0), player(' '), row(0), column(0) {}

Move::Move(const std::string& input) {
  std::istringstream iss(input);
  std::string moveNumberStr;
  std::string playerStr;
  std::string squareStr;
  
  iss >> moveNumberStr;
  iss >> playerStr;
  iss >> squareStr;

  // Parse move number
  try {
    number = std::stoi(moveNumberStr);
    if (number < 1 || number > 9) {
      throw ParseError("Invalid move number. It should be between 1 and 9.");
    }
  } catch (std::invalid_argument const&) {
    throw ParseError("Invalid move number. It should be an integer.");
  }

  // Parse player code
  if (playerStr.length() != 1 || (playerStr[0] != 'X' && playerStr[0] != 'O' && playerStr[0] != 'x' && playerStr[0] != 'o')) {
    throw ParseError("Invalid player code. It should be 'X' or 'O'.");
  }
  player = std::toupper(playerStr[0]);

  // Parse square code
  if (squareStr.length() != 2 || !std::isalpha(squareStr[0]) || !std::isdigit(squareStr[1])) {
    throw ParseError("Invalid square code. It should be a letter followed by a digit.");
  }
  row = std::toupper(squareStr[0]) - 'A' + 1;
  column = squareStr[1] - '0';

  // Check if there's additional invalid input
  std::string extra;
  iss >> extra;
  if (!extra.empty()) {
    throw ParseError("Invalid move format. Extra characters found.");
  }
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  stream << move.number << ' ' << move.player << ' ' << static_cast<char>(move.row - 1 + 'A') << move.column;
  return stream;
}



