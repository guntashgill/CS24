#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Node {
public:
  std::string word;
  std::unordered_set<Node*> related;

  explicit Node(const std::string& str) : word(str) {}
};
class Dictionary {
private:
  // Member Variables
  int getDistance(const std::string& word1, const std::string& word2);
  bool isOneLetterDifference(const std::string& word1, const std::string& word2);
  std::size_t hashFunc(Node* node);

  std::unordered_set<std::string> wordSet;
  std::vector<std::unordered_map<std::string, Node*>> maps;
  std::unordered_map<std::size_t, Node*> hashTable;


public:
  Dictionary(const std::unordered_set<std::string>& words);
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif



