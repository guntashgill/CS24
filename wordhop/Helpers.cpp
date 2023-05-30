#include "Helpers.h"

bool isLowercaseAlpha(const std::string& word) {
  for (char c : word) {
    if (!islower(c)) {
      return false;
    }
  }
  return true;
}


