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
  
  std::unordered_map<std::string, std::string> predecessor;
  std::queue<std::string> bfsQueue;
  bfsQueue.push(from);
  predecessor[from] = "";
  
  while (!bfsQueue.empty()) {
    std::string currentWord = bfsQueue.front();
    bfsQueue.pop();
    
    // Generate neighboring words
    for (size_t i = 0; i < currentWord.length(); ++i) {
      std::string temp = currentWord;
      
      // Replace each character with all possible letters
      for (char c = 'a'; c <= 'z'; ++c) {
        temp[i] = c;
        
        // Check if the modified word exists in the dictionary
        if (dictionary[length].count(temp) > 0 && predecessor.count(temp) == 0) {
          bfsQueue.push(temp);
          predecessor[temp] = currentWord;
          
          if (temp == to) {
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
      }
    }
  }
  
  throw NoChain();
}
