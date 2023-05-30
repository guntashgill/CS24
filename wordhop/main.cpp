#include "Dictionary.h"
#include "Errors.h"

#include <fstream>
#include <iostream>

int main() {
  try {
    // Your test code goes here
    // Example:
    std::unordered_set<std::string> words = {"abc", "abd", "acd", "bcc", "bcd", "bdc", "cdd"};
    Dictionary dict(words);
    std::vector<std::string> chain = dict.hop("abc", "cdd");
    for (const std::string& word : chain) {
      std::cout << word << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}