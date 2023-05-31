#include "Dictionary.h"
#include <istream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

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
    return path;
  }
  int length = from.size();

  if (dictionary[length].find(from) == dictionary[length].end() ||
      dictionary[length].find(to) == dictionary[length].end()) {
    return path;
  }

  std::unordered_map<std::string, std::string> visited;
  std::queue<std::string> queue;
  queue.push(from);
  visited[from] = "";

  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();

    if (current == to) {
      std::string word = current;
      while (!word.empty()) {
        path.push_back(word);
        word = visited[word];
      }
      std::reverse(path.begin(), path.end());
      break;
    }

    for (const auto& neighbor : dictionary[length][current]) {
      if (visited.find(neighbor) == visited.end()) {
        visited[neighbor] = current;
        queue.push(neighbor);
      }
    }
  }

  return path;
}