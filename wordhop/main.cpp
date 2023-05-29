#include "Dictionary.h"
#include "Errors.h"

#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: " << argv[0] << " [words-file]\n";
    return 1;
  }

  Dictionary* dictionary = nullptr;

  try {
    std::ifstream file(argv[1]);
    if (file.fail()) {
      std::cerr << "Could not open file: " << argv[1] << '\n';
      return 1;
    }

    dictionary = Dictionary::create(file);
  }
  catch (const std::exception& e) {
    std::cerr << "Error reading words file: " << e.what() << '\n';
    return 1;
  }

  while (true) {
    std::string from;
    std::string to;

    std::cout << "From: ";
    if (!std::getline(std::cin, from)) {
      break;
    }

    std::cout << "To:   ";
    if (!std::getline(std::cin, to)) {
      break;
    }

    try {
      if (from.length() != to.length()) {
        throw NoChain();  // Throw NoChain exception directly
      }

      std::vector<std::string> chain = dictionary->hop(from, to);
      for (const std::string& word : chain) {
        std::cout << " - " << word << '\n';
      }
    }
    catch (const InvalidWord& e) {
      std::cout << "Invalid word.\n";  // Print "Invalid word." instead of e.what()
    }
    catch (const NoChain& e) {
      std::cout << "No chain.\n";  // Print "No chain." instead of e.what()
    }
    catch (const std::exception& e) {
      std::cerr << "ERROR: " << e.what() << '\n';
    }
  }

  delete dictionary;
  return 0;
}
