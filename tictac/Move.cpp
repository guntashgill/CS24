
#include "Move.h"
#include "Errors.h"

#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
  bool verbose = false;

  // Parse command line arguments
  if (argc == 2 && std::string(argv[1]) == "-v") {
    verbose = true;
  }

  if (verbose) {
    std::cout << "> ";
  }

  std::string inputLine;
  std::getline(std::cin, inputLine);

  try {
    // Attempt to parse the input line into a Move object
    Move move(inputLine);
    std::cout << move << '\n';
    return 0;
  } catch (const ParseError& e) {
    if (verbose) {
      std::cout << "Parse error: " << e.what() << '\n';
    } else {
      std::cout << "Parse error.\n";
    }
    return 1;
  }
}

// Definition of the overloaded << operator for Move object
std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Print move number, player code, row code, and column code in the required format
  stream << move.number << ' ' << move.player << ' ' << static_cast<char>('A' + move.row - 1) << move.column;
  return stream;
}
