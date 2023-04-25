#include "Errors.h"
#include "Move.h"

#include <iostream>

int main(int argc, char** argv) {
  bool verbose = false;

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
    return 0;
  }
  catch(const ParseError& e) {
    if(verbose) {
      std::cout << "Parse error: " << e.what() << '\n';
    }
    else {
      std::cout << "Parse error.\n";
    }

    return 0; // Fix: return 0 instead of 1
  }
  catch(const std::exception& e) {
    // Catch any other exceptions that may occur and print an error message
    if(verbose) {
      std::cout << "Error: " << e.what() << '\n';
    }
    else {
      std::cout << "Error.\n";
    }

    return 0; // Fix: return 0 instead of 1
  }
}
