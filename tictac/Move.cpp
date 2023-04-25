#include "move.h"
#include "errors.h"
#include <iostream>
#include <sstream>
#include <cctype>

Move::Move(const std::string& input) {
  // Use a string stream to parse the input string
  std::stringstream ss(input);

  // Extract move number
  ss >> number;

  // Extract player code
  ss >> player;

  // Extract square code
  std::string squareCode;
  ss >> squareCode;

  // Extract row and column from square code
  row = toupper(squareCode[0]) - 'A' + 1;
  column = squareCode[1] - '0';

  // Ignore any remaining whitespace and comments
  ss >> std::ws;
  std::getline(ss, comment);
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Print move in the expected format
  stream << move.number << " " << move.player << " "
         << static_cast<char>(move.row + 'A' - 1) << move.column;
  if (!move.comment.empty()) {
    stream << " " << move.comment;
  }
  return stream;
}

void invalidMove() {
  std::cerr << "Error: Invalid move." << std::endl;
  exit(1);
}

