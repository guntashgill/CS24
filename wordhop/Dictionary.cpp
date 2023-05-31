#include "Dictionary.h"

#include <istream>
#include <unordered_map>
#include <queue>
#include <set>

Dictionary::Dictionary(std::istream& stream) {
  std::string entry;
  std::unordered_map<int, std::vector<std::string>> wordLengths;

  while (stream >> entry) {
    int length = entry.size();
    dictionary[length][entry] = std::vector<std::string>();

    for (const auto& word : wordLengths[length]) {
      int diffCount = 0;
      for (int i = 0; i < length; i++) {
        if (entry[i] != word[i]) {
          diffCount++;
          if (diffCount > 1) {
            break;
          }
        }
      }

      if (diffCount == 1) {
        dictionary[length][word].push_back(entry);
        dictionary[length][entry].push_back(word);
      }
    }

    wordLengths[length].push_back(entry);
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


