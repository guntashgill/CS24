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

  std::queue<std::pair<int, std::string>> wordChains;
  wordChains.push({0, from});

  while (!wordChains.empty()) {
    std::pair<int, std::string> currChain = wordChains.front();
    wordChains.pop();

    int currLength = currChain.first;
    std::string currWord = currChain.second;

    if (currWord == to) {
      std::vector<std::string> chain;
      std::string word = currWord;

      while (currLength > 0) {
        chain.push_back(word);

        // Find a neighbor with length one less than the current length
        std::vector<std::string> neighbors = getNeighbors(word, wordSet);
        for (const std::string& neighbor : neighbors) {
          if (getDistance(neighbor, to) == currLength - 1) {
            word = neighbor;
            currLength--;
            break;
          }
        }
      }

      chain.push_back(from);
      std::reverse(chain.begin(), chain.end());
      return chain;
    }

    std::vector<std::string> neighbors = getNeighbors(currWord, wordSet);
    for (const std::string& neighbor : neighbors) {
      if (std::find(wordSet.begin(), wordSet.end(), neighbor) != wordSet.end()) {
        wordChains.push({currLength + 1, neighbor});
      }
    }
  }

  throw std::runtime_error("No chain.");
}



