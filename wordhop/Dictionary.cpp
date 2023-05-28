#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>

// Helper function to check if two words differ by exactly one letter
bool isOneLetterDifference(const std::string& word1, const std::string& word2) {
  int diffCount = 0;
  for (size_t i = 0; i < word1.length(); ++i) {
    if (word1[i] != word2[i]) {
      ++diffCount;
      if (diffCount > 1) {
        return false;
      }
    }
  }
  return diffCount == 1;
}

// Helper function to retrieve all valid neighboring words of a given word
std::vector<std::string> getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet) {
  std::vector<std::string> neighbors;
  for (size_t i = 0; i < word.length(); ++i) {
    std::string temp = word;
    for (char c = 'a'; c <= 'z'; ++c) {
      temp[i] = c;
      if (temp != word && wordSet.count(temp) > 0) {
        neighbors.push_back(temp);
      }
    }
  }
  return neighbors;
}

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

// Member function to find a valid chain of words
std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw InvalidWord("The words must have the same length.");
  }

  if (wordSet.count(from) == 0 || wordSet.count(to) == 0) {
    throw InvalidWord("Invalid source or destination word.");
  }

  std::queue<std::vector<std::string>> wordChains;
  wordChains.push({ from });

  while (!wordChains.empty()) {
    std::vector<std::string> currChain = wordChains.front();
    wordChains.pop();

    std::string currWord = currChain.back();
    if (currWord == to) {
      return currChain;
    }

    std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
    for (const std::string& neighbor : neighbors) {
      if (std::find(currChain.begin(), currChain.end(), neighbor) == currChain.end()) {
        std::vector<std::string> newChain = currChain;
        newChain.push_back(neighbor);
        wordChains.push(newChain);
      }
    }
  }

  throw NoChain();
}