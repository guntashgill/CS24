#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <limits>

// Constructor implementation
Dictionary::Dictionary(const std::unordered_set<std::string>& words) : wordSet(words) {}

// Create function implementation
Dictionary* Dictionary::create(std::istream& stream) {
  std::unordered_set<std::string> wordSet;
  std::string word;
  while (stream >> word) {
    wordSet.insert(word);
  }
  Dictionary* dictionary = new Dictionary(wordSet);
  return dictionary;
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw NoChain();
  }

  if (wordSet.count(from) == 0 || wordSet.count(to) == 0) {
    throw InvalidWord("Invalid word.");
  }

  if (from == to) {
    return { from };  // Already at the destination
  }

  std::unordered_map<std::string, std::string> predecessor;
  std::queue<std::string> bfsQueue;
  bfsQueue.push(from);

  while (!bfsQueue.empty()) {
    std::string currentWord = bfsQueue.front();
    bfsQueue.pop();

    // Generate neighboring words
    for (size_t i = 0; i < currentWord.length(); ++i) {
      std::string temp = currentWord;
      for (char c = 'a'; c <= 'z'; ++c) {
        temp[i] = c;
        if (temp == currentWord) {
          continue;
        }
        if (temp == to) {
          // Found the destination word, construct the chain
          std::vector<std::string> chain;
          std::string word = currentWord;
          while (word != from) {
            chain.push_back(word);
            word = predecessor[word];
          }
          chain.push_back(from);
          std::reverse(chain.begin(), chain.end());
          chain.push_back(to);
          return chain;
        }
        if (wordSet.count(temp) != 0 && predecessor.count(temp) == 0) {
          predecessor[temp] = currentWord;
          bfsQueue.push(temp);
        }
      }
    }
  }

  // No chain found
  throw NoChain();
}

