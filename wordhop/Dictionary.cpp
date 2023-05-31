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

// Constructor implementation
Dictionary::Dictionary(const std::unordered_set<std::string>& words) : wordSet(words) {
  // Create connections between neighboring words
  std::unordered_map<std::string, std::vector<std::string>> connections;

  // Iterate over each word in the wordSet
  for (const std::string& word : wordSet) {
    // Generate neighboring words
    for (size_t i = 0; i < word.length(); ++i) {
      std::string temp = word;
      
      // Replace the current character with a wildcard character
      temp[i] = '*';
      
      // Add the modified word to the connections map
      connections[temp].push_back(word);
    }
  }

  // Store the connections in the wordSet
  for (const auto& entry : connections) {
    wordSet.insert(entry.second.begin(), entry.second.end());
  }
}

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

  std::unordered_map<std::string, std::string> predecessor;
  std::queue<std::string> bfsQueue;
  std::unordered_map<std::string, bool> visited;
  bfsQueue.push(from);
  visited[from] = true;

  while (!bfsQueue.empty()) {
    std::string currentWord = bfsQueue.front();
    bfsQueue.pop();

    // Generate neighboring words
    for (size_t i = 0; i < currentWord.length(); ++i) {
      std::string temp = currentWord;
      temp[i] = '*';  // Replace the current character with a wildcard character

      // Find all words in the wordSet that have the same wildcard pattern
      auto iter = wordSet.find(temp);
      while (iter != wordSet.end()) {
        if (!visited[*iter]) {
          visited[*iter] = true;
          predecessor[*iter] = currentWord;
          bfsQueue.push(*iter);

          if (*iter == to) {
            // Found the destination word, construct the chain
            std::vector<std::string> chain;
            std::string word = to;
            while (word != from) {
              chain.push_back(word);
              word = predecessor[word];
            }
            chain.push_back(from);
            std::reverse(chain.begin(), chain.end());
            return chain;
          }
        }
        ++iter;
      }
    }
  }

  // No chain found
  throw NoChain();
}


