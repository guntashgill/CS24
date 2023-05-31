#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_map>

class Dictionary {
private:
  std::unordered_map<int, std::unordered_map<std::string, std::vector<std::string>>> dictionary;

public:
  Dictionary(std::istream& stream);
  static Dictionary* create(std::istream& stream);
  ~Dictionary();
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif


