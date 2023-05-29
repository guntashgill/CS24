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

  std::unordered_map<std::string, std::string> forwardParentMap;
  std::unordered_map<std::string, std::string> backwardParentMap;
  std::unordered_set<std::string> visited;
  std::queue<std::string> forwardQueue;
  std::queue<std::string> backwardQueue;

  visited.insert(from);
  forwardQueue.push(from);
  forwardParentMap[from] = "";

  visited.insert(to);
  backwardQueue.push(to);
  backwardParentMap[to] = "";

  std::string meetingWord = "";

  while (!forwardQueue.empty() && !backwardQueue.empty()) {
    if (forwardQueue.size() <= backwardQueue.size()) {
      meetingWord = expandForward(forwardQueue, visited, forwardParentMap, backwardParentMap);
    } else {
      meetingWord = expandBackward(backwardQueue, visited, forwardParentMap, backwardParentMap);
    }

    if (!meetingWord.empty()) {
      break;  // Found a meeting word, the chains can be connected
    }
  }

  if (meetingWord.empty()) {
    throw NoChain();  // No chain found
  }

  std::vector<std::string> chain;
  std::string currWord = meetingWord;

  while (currWord != "") {
    chain.push_back(currWord);
    currWord = forwardParentMap[currWord];
  }

  std::reverse(chain.begin(), chain.end());

  currWord = backwardParentMap[meetingWord];
  while (currWord != "") {
    chain.push_back(currWord);
    currWord = backwardParentMap[currWord];
  }

  return chain;
}

std::string Dictionary::expandForward(std::queue<std::string>& forwardQueue, std::unordered_set<std::string>& visited, std::unordered_map<std::string, std::string>& forwardParentMap, std::unordered_map<std::string, std::string>& backwardParentMap) {
  std::string currWord = forwardQueue.front();
  forwardQueue.pop();

  std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
  for (const std::string& neighbor : neighbors) {
    if (visited.count(neighbor) == 0) {
      visited.insert(neighbor);
      forwardQueue.push(neighbor);
      forwardParentMap[neighbor] = currWord;

      if (backwardParentMap.count(neighbor) > 0) {
        return neighbor;  // Found a meeting word
      }
    }
  }

  return "";
}

std::string Dictionary::expandBackward(std::queue<std::string>& backwardQueue, std::unordered_set<std::string>& visited, std::unordered_map<std::string, std::string>& forwardParentMap, std::unordered_map<std::string, std::string>& backwardParentMap) {
  std::string currWord = backwardQueue.front();
  backwardQueue.pop();

  std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
  for (const std::string& neighbor : neighbors) {
    if (visited.count(neighbor) == 0) {
      visited.insert(neighbor);
      backwardQueue.push(neighbor);
      backwardParentMap[neighbor] = currWord;

      if (forwardParentMap.count(neighbor) > 0) {
        return neighbor;  // Found a meeting word
      }
    }
  }

  return "";
}