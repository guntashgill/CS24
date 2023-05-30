#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>

class Dictionary {
private:
  // Member Variables
  class TrieNode {
  public:
    bool isWord;
    std::vector<TrieNode*> children;

    TrieNode() : isWord(false), children(26, nullptr) {}

    ~TrieNode() {
      for (TrieNode* child : children) {
        delete child;
      }
    }
  };

  TrieNode* root;

  bool isWordValid(const std::string& word) const;


public:
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
  Dictionary(TrieNode* rootNode);
  ~Dictionary();
};

#endif