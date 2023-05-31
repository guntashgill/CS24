#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Dictionary {
private:
  std::unordered_set<std::string> words;
  std::unordered_map<std::string, std::vector<std::string>> wordConnections;

public:
  Dictionary(std::istream& stream);

  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif
