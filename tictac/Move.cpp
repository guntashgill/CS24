#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <cctype>
#include <sstream>

Move::Move(const std::string& input) {
  // Parse the input string to extract move components
  std::istringstream iss(input);
  iss >> number;
  iss >> player;
  iss >> row;
  iss >> column;


  if (!(iss >> number >> std::ws >> player >> std::ws >> row >> column)) {
    throw ParseError("Invalid input: " + input);
  }

  // Validate move number
  if (number < 1 || number > 9) {
    throw InvalidMove("Invalid move number: " + std::to_string(number));
  }

  // Validate player code
  if (player != 'X' && player != 'O') {
    throw InvalidMove("Invalid player code: " + std::string(1, player));
  }

  // Validate row code
  if (row < 'A' || row > 'C') {
    throw InvalidMove("Invalid row code: " + std::string(1, row));
  }

  // Validate column code
  if (column < '1' || column > '3') {
    throw InvalidMove("Invalid column code: " + std::string(1, column));
  }

  // Extract relevant information from the input and initialize member variables
  number = number;
  player = std::toupper(player);
  row = std::toupper(row);
  column = column;
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Generate the output string for the Move object
  stream << move.number << " " << move.player << " " << static_cast<char>('A' + move.row - 1) << move.column;
  return stream;
}
