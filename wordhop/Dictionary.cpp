#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>

int getDistance(const std::string& word1, const std::string& word2, std::unordered_map<std::string, int>& distanceCache) {
  if (distanceCache.count(word1 + word2))
    return distanceCache[word1 + word2];

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

  int result = distance[m][n];
  distanceCache[word1 + word2] = result;
  return result;
}

bool isOneLetterDifference(const std::string& word1, const std::string& word2) {
  if (word1.length() != word2.length()) {
    return false;
  }

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

std::vector<std::string> getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet) {
  std::vector<std::string> neighbors;
  for (size_t i = 0; i < word.length(); ++i) {
    std::string temp = word;
    for (char c = 'a'; c <= 'z'; ++c) {
      if (c == word[i]) {
        continue;  // Skip the same character
      }
      temp[i] = c;
      if (wordSet.count(temp) > 0) {
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
  std::unordered_set<std::string> words;
  std::string word;
  while (stream >> word) {
    words.insert(word);
  }
  return new Dictionary(words);
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw InvalidWord("No chain.");
  }

  std::unordered_map<std::string, int> distanceCache;

  std::queue<std::vector<std::string>> wordPaths;
  wordPaths.push({from});

  while (!wordPaths.empty()) {
    std::vector<std::string> currentPath = wordPaths.front();
    wordPaths.pop();
    std::string currentWord = currentPath.back();

    if (currentWord == to) {
      return currentPath;
    }

    std::vector<std::string> neighbors = getNeighbors(currentWord, wordSet);
    for (const std::string& neighbor : neighbors) {
      if (std::find(currentPath.begin(), currentPath.end(), neighbor) == currentPath.end()) {
        std::vector<std::string> newPath = currentPath;
        newPath.push_back(neighbor);
        wordPaths.push(newPath);
      }
    }
  }

  throw InvalidWord("No chain.");
}





