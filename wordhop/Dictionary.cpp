#include "Dictionary.h"
#include "Errors.h"
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <queue>
#include "Helpers.h"

// Trie Node
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

// Dictionary Implementation
Dictionary* Dictionary::create(std::istream& stream) {
  TrieNode* root = new TrieNode();
  std::string word;

  while (std::getline(stream, word)) {
    if (isValidWord(word)) {
      TrieNode* node = root;
      for (char c : word) {
        int index = c - 'a';
        if (!node->children[index]) {
          node->children[index] = new TrieNode();
        }
        node = node->children[index];
      }
      node->isWord = true;
    }
  }

  return new Dictionary(root);
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (!isValidWord(from)) {
    throw InvalidWord(from);
  }

  if (!isValidWord(to)) {
    throw InvalidWord(to);
  }

  if (from.length() != to.length()) {
    throw NoChain();
  }

  if (from == to) {
    return {from};
  }

  std::unordered_set<std::string> visited;
  std::queue<std::vector<std::string>> wordChains;
  wordChains.push({from});

  while (!wordChains.empty()) {
    std::vector<std::string> chain = wordChains.front();
    wordChains.pop();

    const std::string& lastWord = chain.back();

    for (size_t i = 0; i < lastWord.length(); ++i) {
      std::string word = lastWord;
      for (char c = 'a'; c <= 'z'; ++c) {
        word[i] = c;

        if (word == to) {
          chain.push_back(to);
          return chain;
        }

        if (visited.find(word) == visited.end() && isWordValid(word)) {
          visited.insert(word);
          std::vector<std::string> newChain = chain;
          newChain.push_back(word);
          wordChains.push(std::move(newChain));
        }
      }
    }
  }

  throw NoChain();
}

bool Dictionary::isWordValid(const std::string& word) const {
  TrieNode* node = root;
  for (char c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      return false;
    }
    node = node->children[index];
  }
  return node->isWord;
}
Dictionary::Dictionary(TrieNode* rootNode) : root(rootNode) {}

Dictionary::~Dictionary() {
  delete root;
}