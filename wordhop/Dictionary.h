#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

class Dictionary {
  std::unordered_set<std::string> words;

  // Helper Functions
  void insertWord(const std::string& word);

public:
  // Constructor for the Dictionary class
  Dictionary(std::istream& stream);

  // Static function to create a new Dictionary object from an input stream
  static Dictionary* create(std::istream& stream);

  // Function to find a valid chain of words from "from" to "to"
  std::vector<std::string> hop(const std::string& from, const std::string& to);

  // Custom exceptions
  class InvalidWord {};
  class NoChain {};
};

#endif
