
#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <limits>

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
    throw InvalidWord("Invalid word.");
  }

  if (from == to) {
    return { from };  // Already at the destination
  }

  std::unordered_map<std::string, std::string> parentMap;
  std::unordered_set<std::string> visited;
  std::queue<std::string> wordQueue;

  visited.insert(from);
  wordQueue.push(from);

  while (!wordQueue.empty()) {
    std::string currWord = wordQueue.front();
    wordQueue.pop();

    if (currWord == to) {
      break;  // Found a valid chain
    }

    std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
    for (const std::string& neighbor : neighbors) {
      if (visited.count(neighbor) == 0) {
        visited.insert(neighbor);
        parentMap[neighbor] = currWord;
        wordQueue.push(neighbor);
      }
    }
  }

  if (parentMap.count(to) == 0) {
    throw NoChain();  // No chain found
  }

  std::vector<std::string> chain;
  std::string currWord = to;
  while (currWord != "") {
    chain.push_back(currWord);
    currWord = parentMap[currWord];
  }
  std::reverse(chain.begin(), chain.end());

  return chain;
}