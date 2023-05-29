#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_map>

class Dictionary {
private:
  // Member Variables
 std::unordered_map<int, std::vector<std::string>> words;


public:
  Dictionary(std::istream& stream);
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif



