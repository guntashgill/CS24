#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <cctype>
#include <sstream>

Move::Move(const std::string& input) {
  // Parse the input string and validate it
  std::istringstream iss(input);
  int moveNumber;
  char playerCode;
  char rowCode;
  char columnCode;
  std::string comment;

  if (!(iss >> moveNumber >> std::ws >> playerCode >> std::ws >> rowCode >> columnCode)) {
    throw ParseError("Invalid input: " + input);
  }

  // Validate move number
  if (moveNumber < 1 || moveNumber > 9) {
    throw InvalidMove("Invalid move number: " + std::to_string(moveNumber));
  }

  // Validate player code
  if (playerCode != 'X' && playerCode != 'O') {
    throw InvalidMove("Invalid player code: " + std::string(1, playerCode));
  }

  // Validate row code
  if (rowCode < 'A' || rowCode > 'C') {
    throw InvalidMove("Invalid row code: " + std::string(1, rowCode));
  }

  // Validate column code
  if (columnCode < '1' || columnCode > '3') {
    throw InvalidMove("Invalid column code: " + std::string(1, columnCode));
  }

  // Extract relevant information from the input and initialize member variables
  number = moveNumber;
  player = std::toupper(playerCode);
  row = std::toupper(rowCode);
  column = columnCode;
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Generate the output string for the Move object
  stream << move.number << " " << move.player << " " << move.row << move.column;
  return stream;
}
