#include "Dictionary.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

Dictionary* Dictionary::create(std::istream& stream) {
  Dictionary* dictionary = new Dictionary();
  std::string word;
  while (stream >> word) {
    if (dictionary->isValidWord(word)) {
      dictionary->wordList.push_back(word);
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
  wordChain.push_back(from);
  std::vector<std::string> visitedWords;
  visitedWords.push_back(from);
  while (!wordChain.empty()) {
    std::string currentWord = wordChain.front();
    wordChain.erase(wordChain.begin());
    for (const std::string& word : wordList) {
      if (word.length() != currentWord.length()) {
        continue;
      }

      int diffCount = 0;
      for (size_t i = 0; i < word.length(); i++) {
        if (word[i] != currentWord[i]) {
          diffCount++;
        }
      }

      if (diffCount == 1 && std::find(visitedWords.begin(), visitedWords.end(), word) == visitedWords.end()) {
        wordChain.push_back(word);
        visitedWords.push_back(word);

        if (word == to) {
          wordChain.push_back(to);
          return wordChain;
        }
      }
    }
  }
  throw std::runtime_error("No Chain");
}
