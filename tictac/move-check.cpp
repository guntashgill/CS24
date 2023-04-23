#include "Errors.h"
#include "Move.h"

#include <iostream>


int main(int argc, char** argv) {
  bool verbose = false;
  int exitCode = 0; // Initialize exit code to 0

  if(argc == 2 && std::string(argv[1]) == "-v") {
    verbose = true;
  }

  if(verbose) {
    std::cout << "> ";
  }

  std::string line;
  std::getline(std::cin, line);

  try {
    Move move(line);
    std::cout << move << '\n';

    // Additional logic to check if move meets expected criteria
    if (move.row < 1 || move.row > 3 || move.column < 1 || move.column > 3) {
      exitCode = 1; // Set exit code to 1 if move is not valid
    }
  }
  catch(const ParseError& e) {
    if(verbose) {
      std::cout << "Parse error: " << e.what() << '\n';
    }
    else {
      std::cout << "Parse error.\n";
    }
    exitCode = 1; // Set exit code to 1 on parsing error
  }

  return exitCode; // Return the correct exit code
}

