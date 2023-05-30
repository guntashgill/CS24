#include "Helpers.h"
#include <algorithm>

bool isValidWord(const std::string& word) {
  return !word.empty() && std::all_of(word.begin(), word.end(), [](char c) {
    return std::islower(c);
  });
}


