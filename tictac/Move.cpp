#include "Move.h"
#include "Errors.h"
#include <iostream>
#include <sstream>
#include <cctype>

Move::Move(const std::string& input) {
  // Use a string stream to parse the input string
  std::stringstream ss(input);
  char c;
  std::string temp;

  if (!(ss >> number >> player >> row >> column)) {
    throw MoveError("Failed to parse move");
  }

  if (!(ss >> c) || c != '\n') {
    throw MoveError("Unexpected character after move");
  }


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
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Print move in the expected format
  stream << move.number << " " << move.player << " "
         << static_cast<char>(move.row + 'A' - 1) << move.column;
  return stream;
}

void invalidMove() {
  std::cerr << "Error: Invalid move." << std::endl;
  exit(1);
}