#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <bitset>

Dictionary::Dictionary(const std::unordered_set<std::string>& words) : wordSet(words), connections() {}

bool Dictionary::isOneLetterDifference(const std::string& word1, const std::string& word2) const {
  if (word1.length() != word2.length()) {
    return false;
  }

  int diffCount = 0;
  for (size_t i = 0; i < word1.length(); ++i) {
    if (word1[i] != word2[i]) {
      ++diffCount;
    }
  }

  return diffCount == 1;
}

Dictionary* Dictionary::create(std::istream& stream) {
  std::unordered_set<std::string> wordSet;
  std::string word;
  while (stream >> word) {
    wordSet.insert(word);
  }

  Dictionary* dictionary = new Dictionary(wordSet);

  return dictionary;
}

void Dictionary::generateConnections() {
  for (const std::string& word : wordSet) {
    std::vector<std::string> neighbors;
    std::string currentWord = word;

    for (size_t i = 0; i < word.length(); ++i) {
      char originalChar = currentWord[i];

      // Generate a bitset with all bits set to 1
      std::bitset<26> mask;
      mask.set();

      // Set the bit corresponding to the original character to 0
      mask.reset(originalChar - 'a');

      // Iterate over the positions where the bit is set to 1
      for (size_t j = 0; j < 26; ++j) {
        if (mask.test(j)) {
          currentWord[i] = static_cast<char>('a' + j);

          if (wordSet.count(currentWord) > 0 && isOneLetterDifference(word, currentWord)) {
            neighbors.push_back(currentWord);
          }
        }
      }

      currentWord[i] = originalChar; // Restore the original character
    }

    connections[word] = neighbors;
  }
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw NoChain();
  }

  if (wordSet.count(from) == 0 || wordSet.count(to) == 0) {
    throw InvalidWord("Invalid word.");
  }

  if (connections.empty()) {
    generateConnections();  // Generate connections if not already done
  }

  if (from == to) {
    return {from};  // Already at the destination
  }

  std::unordered_map<std::string, std::string> parentMap;
  std::unordered_map<std::string, int> distanceMap;
  std::queue<std::string> queue;

  parentMap[from] = "";
  distanceMap[from] = 0;
  queue.push(from);

  while (!queue.empty()) {
    std::string currWord = queue.front();
    queue.pop();

    const std::vector<std::string>& neighbors = connections[currWord];
    for (const std::string& neighbor : neighbors) {
      if (distanceMap.count(neighbor) == 0) {
        distanceMap[neighbor] = distanceMap[currWord] + 1;
        parentMap[neighbor] = currWord;
        if (neighbor == to) {
          // Found the destination word, construct the chain and return it
          std::vector<std::string> chain;
          std::string word = to;
          while (word != "") {
            chain.push_back(word);
            word = parentMap[word];
          }
          std::reverse(chain.begin(), chain.end());
          return chain;
        }
        queue.push(neighbor);
      }
    }
  }

  throw NoChain();  // No chain found
}


