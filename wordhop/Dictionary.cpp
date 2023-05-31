#include "Dictionary.h"
#include <istream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Errors.h"

Dictionary::Dictionary(std::istream& stream) {
  std::string entry;

  while (stream >> entry) {
    int length = entry.size();
    dictionary[length][entry] = std::vector<std::string>();

    for (int i = 0; i < length; i++) {
      std::string modifiedWord = entry;
      for (char c = 'a'; c <= 'z'; c++) {
        modifiedWord[i] = c;
        if (modifiedWord != entry && dictionary[length].count(modifiedWord) > 0) {
          dictionary[length][entry].push_back(modifiedWord);
        }
      }
    }
  }
}

Dictionary* Dictionary::create(std::istream& stream) {
  return new Dictionary(stream);
}

Dictionary::~Dictionary() {}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  std::vector<std::string> path;
  
  if (from.size() != to.size()) {
    throw InvalidWord("Invalid word.");
  }
  
  int length = from.size();
  
  if (dictionary[length].find(from) == dictionary[length].end() ||
      dictionary[length].find(to) == dictionary[length].end()) {
    throw InvalidWord("Invalid word.");
  }
  
  std::unordered_map<std::string, bool> visited;
  
  dfs(from, to, visited, path);
  
  if (path.empty()) {
    throw NoChain();
  }
  
  return path;
}


void Dictionary::dfs(const std::string& current, const std::string& target, std::unordered_map<std::string, bool>& visited, std::vector<std::string>& path) {
  visited[current] = true;
  path.push_back(current);

  if (current == target) {
    return;  // Reached the target word, stop the recursion
  }

  for (const auto& neighbor : dictionary[current.size()][current]) {
    if (!visited[neighbor]) {
      dfs(neighbor, target, visited, path);

      if (path.back() == target) {
        return;  // Found a path to the target, stop the recursion
      }

      path.pop_back();
    }
  }

  visited[current] = false;  // Reset the visited flag for backtracking
}