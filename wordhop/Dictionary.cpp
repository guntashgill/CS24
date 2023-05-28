#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>

// Helper function to calculate the Levenshtein distance between two words
int getDistance(const std::string& word1, const std::string& word2) {
  int m = word1.length();
  int n = word2.length();

  // Create a 2D distance matrix
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

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (from.length() != to.length()) {
    throw InvalidWord("The words must have the same length.");
  }

  if (wordSet.count(from) == 0 || wordSet.count(to) == 0) {
    throw InvalidWord("Invalid source or destination word.");
  }

  std::unordered_set<std::string> visitedFrom;   // Track visited words from 'from' side
  std::unordered_set<std::string> visitedTo;     // Track visited words from 'to' side
  std::unordered_map<std::string, std::string> fromParents;  // Track word parents from 'from' side
  std::unordered_map<std::string, std::string> toParents;    // Track word parents from 'to' side

  std::queue<std::string> fromQueue;   // Queue for 'from' side exploration
  std::queue<std::string> toQueue;     // Queue for 'to' side exploration

  visitedFrom.insert(from);
  visitedTo.insert(to);
  fromQueue.push(from);
  toQueue.push(to);

  std::string intersectWord;  // Common word where the two searches meet

  while (!fromQueue.empty() && !toQueue.empty()) {
    // Explore from 'from' side
    if (!fromQueue.empty()) {
      std::string currWord = fromQueue.front();
      fromQueue.pop();

      std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
      for (const std::string& neighbor : neighbors) {
        if (visitedFrom.count(neighbor) == 0) {
          visitedFrom.insert(neighbor);
          fromParents[neighbor] = currWord;
          fromQueue.push(neighbor);

          if (visitedTo.count(neighbor) > 0) {
            intersectWord = neighbor;
            break;
          }
        }
      }

      if (!intersectWord.empty()) {
        break;
      }
    }

    // Explore from 'to' side
    if (!toQueue.empty()) {
      std::string currWord = toQueue.front();
      toQueue.pop();

      std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
      for (const std::string& neighbor : neighbors) {
        if (visitedTo.count(neighbor) == 0) {
          visitedTo.insert(neighbor);
          toParents[neighbor] = currWord;
          toQueue.push(neighbor);

          if (visitedFrom.count(neighbor) > 0) {
            intersectWord = neighbor;
            break;
          }
        }
      }

      if (!intersectWord.empty()) {
        break;
      }
    }
  }

  if (intersectWord.empty()) {
    throw NoChain();
  }

  // Construct the word chain from 'from' side to the intersect word
  std::vector<std::string> chainFrom;
  std::string currWord = intersectWord;
  while (currWord != from) {
    chainFrom.push_back(currWord);
    currWord = fromParents[currWord];
  }
  chainFrom.push_back(from);
  std::reverse(chainFrom.begin(), chainFrom.end());

  // Construct the word chain from 'to' side to the intersect word
  std::vector<std::string> chainTo;
  currWord = intersectWord;
  while (currWord != to) {
    chainTo.push_back(currWord);
    currWord = toParents[currWord];
  }
  chainTo.push_back(to);

  // Concatenate the 'from' and 'to' chains to form the complete word chain
  chainFrom.insert(chainFrom.end(), chainTo.begin(), chainTo.end());

  return chainFrom;
}
