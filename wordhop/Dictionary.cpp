#include "Dictionary.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

Dictionary* Dictionary::create(std::istream& stream) {
  Dictionary* dictionary = new Dictionary();
  std::string word;
  while (stream >> word) {
    if (dictionary->isValidWord(word)) {
      dictionary->wordSet.insert(word);
      dictionary->wordLengths.insert(word.length());
    }
  }
  return dictionary;
}

bool Dictionary::isValidWord(const std::string& word) const {
  if (word.empty() || !std::all_of(word.begin(), word.end(), ::islower)) {
    return false;
  }
  return true;
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) const {
  if (!isValidWord(from) || !isValidWord(to)) {
    throw std::invalid_argument("Invalid Word");
  }
  if (from.length() != to.length()) {
    throw std::invalid_argument("Words must have the same length");
  }
  if (from == to) {
    return {from};
  }

  std::vector<std::string> wordChain;
  wordChain.reserve(wordSet.size());
  std::unordered_set<std::string> visitedWords;
  visitedWords.reserve(wordSet.size());
  wordChain.push_back(from);
  visitedWords.insert(from);

  while (!wordChain.empty()) {
    std::string currentWord = std::move(wordChain.back());
    wordChain.pop_back();

    for (const std::string& word : wordSet) {
      if (word.length() != currentWord.length() || visitedWords.count(word) > 0) {
        continue;
      }

      int diffCount = 0;
      for (size_t i = 0; i < word.length(); i++) {
        if (word[i] != currentWord[i]) {
          diffCount++;
        }
      }

      if (diffCount == 1) {
        wordChain.push_back(word);
        visitedWords.insert(word);

        if (word == to) {
          wordChain.push_back(to);
          return wordChain;
        }
      }
    }
  }
  throw std::runtime_error("No Chain");
}
