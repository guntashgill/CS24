#include "Dictionary.h"
#include "Errors.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <unordered_map>

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

bool Dictionary::isOneLetterDifference(const std::string& word1, const std::string& word2) {
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


std::size_t Dictionary::hashFunc(Node* node) {
  std::hash<std::string> hasher;
  return hasher(node->word);
}
Dictionary::Dictionary(const std::unordered_set<std::string>& words) : wordSet(words) {
  // Create massive hash table
  int maxSize = words.size() * 2;
  hashTable.reserve(maxSize);

  // Initialize unordered map of maps
  maps.resize(32);  // Assuming you have 32 different lengths of words

  for (const auto& word : words) {
    int wordLength = word.length();
    maps[wordLength].reserve(maxSize);
    maps[wordLength][word] = new Node(word);
  }

  // Hashing all the values
  for (auto& map : maps) {
    for (auto& [word, node] : map) {
      // Compare with other elements in the same map
      for (auto it = std::next(map.begin()); it != map.end(); ++it) {
        if (isOneLetterDifference(word, it->first)) {
          node->related.insert(it->second);
          it->second->related.insert(node);
        }
      }
      // Hash the Node* and remove it from the map
      hashTable[hashFunc(node)] = node;
      map.erase(word);
    }
  }
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

    if (visitedTo.count(currWordFrom) > 0) {
      std::reverse(currChainFrom.begin(), currChainFrom.end());
      currChainFrom.insert(currChainFrom.end(), currChainTo.begin(), currChainTo.end());
      return currChainFrom;
    }

    if (visitedFrom.count(currWordTo) > 0) {
      std::reverse(currChainTo.begin(), currChainTo.end());
      currChainTo.insert(currChainTo.end(), currChainFrom.begin(), currChainFrom.end());
      return currChainTo;
    }

    std::unordered_set<Node*>& relatedFrom = hashTable[hashFunc(maps[currWordFrom.length() - 1][currWordFrom])]->related;
    std::unordered_set<Node*>& relatedTo = hashTable[hashFunc(maps[currWordTo.length() - 1][currWordTo])]->related;

    for (Node* relatedNode : relatedFrom) {
      if (visitedFrom.count(relatedNode->word) == 0) {
        visitedFrom.insert(relatedNode->word);
        std::vector<std::string> newChainFrom = currChainFrom;
        newChainFrom.push_back(relatedNode->word);
        wordChainsFrom.push(newChainFrom);
      }
    }

    for (Node* relatedNode : relatedTo) {
      if (visitedTo.count(relatedNode->word) == 0) {
        visitedTo.insert(relatedNode->word);
        std::vector<std::string> newChainTo = currChainTo;
        newChainTo.push_back(relatedNode->word);
        wordChainsTo.push(newChainTo);
      }
    }
  }

  throw NoChain();
}