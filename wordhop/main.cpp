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
    if (!file.is_open()) {
      throw std::runtime_error("Could not open file: " + std::string(argv[1]));
    }

    dictionary = Dictionary::create(file);
    file.close();
  }
  catch (const std::exception& e) {
    std::cerr << "Error reading words file: " << e.what() << '\n';
    delete dictionary; // Clean up dictionary if it was created
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
      std::vector<std::string> chain = dictionary->hop(from, to);
      for (const std::string& word : chain) {
        std::cout << " - " << word << '\n';
      }
    }
    catch (const std::runtime_error& e) {
      std::cout << e.what() << '\n';
    }
    catch (const InvalidWord& e) {
      std::cout << "Invalid word: " << e.what() << '\n';
    }
    catch (const NoChain& e) {
      std::cout << e.what() << '\n';
    }
    catch (const std::exception& e) {
      std::cerr << "ERROR: " << e.what() << '\n';
    }
  }

  delete dictionary;
  return 0;
}
