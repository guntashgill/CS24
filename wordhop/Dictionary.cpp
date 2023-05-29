#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>

int getDistance(const std::string& word1, const std::string& word2) {
  int m = word1.length();
  int n = word2.length();

  std::vector<std::vector<int>> distance(m + 1, std::vector<int>(n + 1));

  // Initialize the first row and column of the matrix
  for (int i = 0; i <= m; ++i) {
    distance[i][0] = i;
  }
  for (int j = 0; j <= n; ++j) {
    distance[0][j] = j;
  }

  // Calculate the minimum edit distance
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int substitutionCost = (word1[i - 1] != word2[j - 1]) ? 1 : 0;
      distance[i][j] = std::min({distance[i - 1][j] + 1, distance[i][j - 1] + 1, distance[i - 1][j - 1] + substitutionCost});
    }
  }

  return distance[m][n];
}

bool isOneLetterDifference(const std::string& word1, const std::string& word2) {
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

std::vector<std::string> getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet) {
  std::vector<std::string> neighbors;
  for (size_t i = 0; i < word.length(); ++i) {
    std::string temp = word;
    for (char c = 'a'; c <= 'z'; ++c) {
      if (c == word[i]) {
        continue;  // Skip the same character
      }
      temp[i] = c;
      if (wordSet.count(temp) > 0 && isOneLetterDifference(word, temp)) {
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

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw NoChain();
  }

  if (wordSet.count(from) == 0 || wordSet.count(to) == 0) {
    throw InvalidWord("Invalid source or destination word.");
  }

  if (from == to) {
    return { from };  // Already at the destination
  }

  std::queue<std::vector<std::string>> wordChainsFrom;
  std::queue<std::vector<std::string>> wordChainsTo;
  std::unordered_set<std::string> visitedFrom;
  std::unordered_set<std::string> visitedTo;
  visitedFrom.insert(from);
  visitedTo.insert(to);
  wordChainsFrom.push({ from });
  wordChainsTo.push({ to });

  while (!wordChainsFrom.empty() && !wordChainsTo.empty()) {
    std::vector<std::string> currChainFrom = wordChainsFrom.front();
    std::vector<std::string> currChainTo = wordChainsTo.front();
    wordChainsFrom.pop();
    wordChainsTo.pop();

    std::string currWordFrom = currChainFrom.back();
    std::string currWordTo = currChainTo.back();

    // Check for intersection
    if (visitedFrom.count(currWordTo) > 0) {
      currChainTo.insert(currChainTo.end(), currChainFrom.rbegin(), currChainFrom.rend());
      return currChainTo;  // Found a chain from "from" to "to"
    }

    // Expand from "from" side
    std::vector<std::string> neighborsFrom = getNeighbors(currWordFrom, wordSet);
    for (const std::string& neighbor : neighborsFrom) {
      if (visitedFrom.count(neighbor) == 0) {
        std::vector<std::string> newChainFrom = currChainFrom;
        newChainFrom.push_back(neighbor);
        wordChainsFrom.push(newChainFrom);
        visitedFrom.insert(neighbor);

        // Check for intersection after adding a new word to the "from" side
        if (visitedTo.count(neighbor) > 0) {
          currChainTo.insert(currChainTo.end(), newChainFrom.rbegin(), newChainFrom.rend());
          return currChainTo;  // Found a chain from "from" to "to"
        }
      }
    }

    // Expand from "to" side
    std::vector<std::string> neighborsTo = getNeighbors(currWordTo, wordSet);
    for (const std::string& neighbor : neighborsTo) {
      if (visitedTo.count(neighbor) == 0) {
        std::vector<std::string> newChainTo = currChainTo;
        newChainTo.push_back(neighbor);
        wordChainsTo.push(newChainTo);
        visitedTo.insert(neighbor);

        // Check for intersection after adding a new word to the "to" side
        if (visitedFrom.count(neighbor) > 0) {
          currChainFrom.insert(currChainFrom.end(), newChainTo.rbegin(), newChainTo.rend());
          return currChainFrom;  // Found a chain from "from" to "to"
        }
      }
    }
  }

  throw NoChain();  // No chain found
}
