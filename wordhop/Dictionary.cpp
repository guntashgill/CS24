#include "Dictionary.h"
#include "Errors.h"

#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <unordered_map>

// Helper function to check if two words differ by exactly one letter
bool isValidHop(const std::string& word1, const std::string& word2) {
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

// Dictionary constructor
Dictionary::Dictionary(std::istream& stream) {
  std::string word;
  while (std::getline(stream, word)) {
    if (word.empty() || word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos) {
      continue; // Ignore blank lines and non-lowercase ASCII letters
    }
    words.insert(word);
  }

  // Precompute word connections
  for (const std::string& word : words) {
    std::vector<std::string> connections;
    for (size_t i = 0; i < word.length(); ++i) {
      std::string newWord = word;
      for (char c = 'a'; c <= 'z'; ++c) {
        if (c != word[i]) {
          newWord[i] = c;
          if (words.find(newWord) != words.end() && isValidHop(word, newWord)) {
            connections.push_back(newWord);
          }
        }
      }
    }
    wordConnections[word] = connections;
  }
}

// Create function used by the autograder
Dictionary* Dictionary::create(std::istream& stream) {
  return new Dictionary(stream);
}

// Function to find a valid chain of words from 'from' to 'to'
std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (words.find(from) == words.end() || words.find(to) == words.end()) {
    throw InvalidWord("One or both of the words are not valid.");
  }

  if (from.length() != to.length()) {
    throw InvalidWord("Words must be of the same length.");
  }

  if (from == to) {
    return {from}; // Return the word itself as the only element in the chain
  }

  std::unordered_set<std::string> visited;
  visited.insert(from);

  std::unordered_map<std::string, std::string> predecessor;
  predecessor[from] = "";

  std::queue<std::string> queue;
  queue.push(from);

  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();

    for (const std::string& nextWord : wordConnections[current]) {
      if (visited.find(nextWord) == visited.end()) {
        visited.insert(nextWord);
        queue.push(nextWord);
        predecessor[nextWord] = current;
        if (nextWord == to) {
          std::vector<std::string> chain;
          std::string word = to;
          while (!word.empty()) {
            chain.push_back(word);
            word = predecessor[word];
          }
          std::reverse(chain.begin(), chain.end());
          return chain;
        }
      }
    }
  }

  throw NoChain(); // No valid chain exists
}



