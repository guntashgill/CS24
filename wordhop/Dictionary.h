#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>

class Dictionary {
private:
  // Member Variables
  std::vector<std::string> wordList;

  // Helper Functions
  bool isValidWord(const std::string& word) const;

public:
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to) const;
};

#endif

