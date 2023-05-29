#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Dictionary {
private:
  // Member Variables
  std::unordered_set<std::string> wordSet;
  std::vector<std::string> getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet);
  std::string expandForward(std::queue<std::string>& forwardQueue,std::unordered_set<std::string>& visited,std::unordered_map<std::string, std::string>& forwardParentMap,std::unordered_map<std::string, std::string>& backwardParentMap);
  std::string expandBackward(std::queue<std::string>& backwardQueue, std::unordered_set<std::string>& visited, std::unordered_map<std::string, std::string>& forwardParentMap,std::unordered_map<std::string, std::string>& backwardParentMap);


public:
  Dictionary(const std::unordered_set<std::string>& words);
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif


