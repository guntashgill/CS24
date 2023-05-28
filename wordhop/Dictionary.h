#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Dictionary {
private:
  // Member Variables
  std::unordered_set<std::string> wordSet; 


public:
  Dictionary(const std::unordered_set<std::string>& words);
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif


