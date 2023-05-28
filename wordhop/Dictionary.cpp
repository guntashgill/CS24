
#include "Dictionary.h"
#include "Errors.h"
#include "Helpers.h"

#include <fstream>

Dictionary* Dictionary::create(std::istream& stream) {
  Dictionary* dictionary = new Dictionary();
  std::string word;
  
  while (stream >> word) {
    if (isLowercaseAlpha(word)) {
      dictionary->words.insert(word);
    }
  }
  
  return dictionary;
}

std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
  if (!isLowercaseAlpha(from) || !isLowercaseAlpha(to)) {
    throw InvalidWord("Invalid word");
  }

  if (from.length() != to.length()) {
    throw NoChain();
  }
  
  std::vector<std::string> chain;
  chain.push_back(from);
  
  if (from == to) {
    return chain;
  }
  
  std::unordered_set<std::string> visited;
  visited.insert(from);
  
  std::unordered_map<std::string, std::string> parent;
  parent[from] = "";

  while (!chain.empty()) {
    std::string current = chain.front();
    chain.erase(chain.begin());
    
    for (std::size_t i = 0; i < current.length(); i++) {
      std::string word = current;
      
      for (char c = 'a'; c <= 'z'; c++) {
        if (c == current[i]) {
          continue;
        }
        
        word[i] = c;
        
        if (word == to) {
          chain.push_back(word);
          
          while (!parent[word].empty()) {
            chain.insert(chain.begin(), parent[word]);
            word = parent[word];
          }
          
          return chain;
        }
        
        if (words.find(word) != words.end() && visited.find(word) == visited.end()) {
          visited.insert(word);
          chain.push_back(word);
          parent[word] = current;
        }
      }
    }
  }
  
  throw NoChain();
}
