#include "Errors.h"
#include "Move.h"

#include <sstream>

Move::Move(const std::string& input) {
  std::istringstream iss(input);
  iss >> number;
  iss >> player;
  iss >> row;
  iss >> column;

  if (iss.fail() || !iss.eof()) {
    throw ParseError("Invalid move format.");
  }
}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  stream << move.number << " " << move.player << " " << static_cast<char>('A' + move.row) << move.column;
  return stream;
}
