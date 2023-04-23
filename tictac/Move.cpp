
#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

Move::Move(const std::string& input) {
  size_t pos = 0;
  size_t next_pos = 0;
  

  number = std::stoi(input, &next_pos);
  if (next_pos == pos || input[next_pos] != ' ') {
    throw ParseError("Failed to parse Move: " + input);
  }
  pos = next_pos + 1;

  if (pos >= input.length() || input[pos] == ' ') {
    throw ParseError("Failed to parse Move: " + input); 
  }
  player = input[pos];
  pos += 2;

  if (pos >= input.length() || input[pos] != ' ') {
    throw ParseError("Failed to parse Move: " + input);
  }
  pos += 1;
  next_pos = input.find(' ', pos);
  if (next_pos == std::string::npos) {
    throw ParseError("Failed to parse Move: " + input); 
  }
  row = std::stoi(input.substr(pos, next_pos - pos), &next_pos);
  if (next_pos == pos || input[next_pos] != ' ') {
    throw ParseError("Failed to parse Move: " + input); 
  }
  pos = next_pos + 1;

  if (pos >= input.length()) {
    throw ParseError("Failed to parse Move: " + input); 
  }
  column = std::stoi(input.substr(pos));
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
  stream << move.number << " " << move.player << " " << move.row << " " << move.column;
  return stream;
}