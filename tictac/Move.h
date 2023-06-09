#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>

struct Move {
  // Member Variables
  int number;
  char player;
  int row;
  int column;

  // The constructor parses a string.
  Move(const std::string& input);
};

// Adding a << operator allows easy printing to std::cout.
// This should print the Move in the format described in the readme.
std::ostream& operator<<(std::ostream& stream, const Move& move);

#endif

