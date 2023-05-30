#include "Dictionary.h"
#include "Errors.h"

#include <unordered_set>
#include <unordered_map>
#include <queue>

// Helper function to check if two words differ by exactly one letter
bool isOneLetterDifference(const std::string& word1, const std::string& word2) {
  int diffCount = 0;
  for (size_t i = 0; i < word1.length(); ++i) {
    if (word1[i] != word2[i]) {
      if (++diffCount > 1) {
        return false;
      }
    }
  }
  return diffCount == 1;
}

// Helper function to perform breadth-first search (BFS) to find the shortest word chain
std::vector<std::string> bfs(const std::string& from, const std::string& to, const std::unordered_set<std::string>& wordSet) {
  std::unordered_map<std::string, std::string> parentMap;
  std::queue<std::string> queue;
  queue.push(from);

  while (!queue.empty()) {
    std::string currentWord = queue.front();
    queue.pop();

    if (currentWord == to) {
      // Found the target word, construct the word chain
      std::vector<std::string> chain;
      chain.push_back(currentWord);

      while (currentWord != from) {
        currentWord = parentMap[currentWord];
        chain.push_back(currentWord);
      }

      std::reverse(chain.begin(), chain.end());
      return chain;
    }

    for (const std::string& word : wordSet) {
      if (isOneLetterDifference(currentWord, word) && parentMap.find(word) == parentMap.end()) {
        queue.push(word);
        parentMap[word] = currentWord;
      }
    }
  }

  throw NoChain(); // No valid word chain found
}

// Constructor
Dictionary::Dictionary(const std::unordered_set<std::string>& words) : wordSet(words) {}

// Create a Dictionary from an input stream
Dictionary* Dictionary::create(std::istream& stream) {
  std::unordered_set<std::string> wordSet;
  std::string word;

  while (stream >> word) {
    wordSet.insert(word);
  }

  Dictionary* dictionary = new Dictionary(wordSet);
  return dictionary;
}

// Return a valid chain of words from 'from' to 'to'
std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (wordSet.find(from) == wordSet.end() || wordSet.find(to) == wordSet.end()) {
    throw InvalidWord((wordSet.find(from) == wordSet.end()) ? from : to);
  }

  if (from.length() != to.length()) {
    throw InvalidWord("Words must have the same length.");
  }

  return bfs(from, to, wordSet);
}

