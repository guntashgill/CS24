#include "dictionary.h"
#include "errors.h"
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

// Helper function to check if two words differ by exactly one letter
bool isOneLetterDifference(const std::string& word1, const std::string& word2) {
    int diffCount = 0;
    int len = word1.length();
    for (int i = 0; i < len; i++) {
        if (word1[i] != word2[i]) {
            diffCount++;
            if (diffCount > 1) {
                return false;
            }
        }
    }
    return diffCount == 1;
}

// Helper function to generate the word chain
std::vector<std::string> generateWordChain(const std::unordered_map<std::string, std::string>& predecessors, const std::string& startWord, const std::string& endWord) {
    std::vector<std::string> wordChain;
    std::string currentWord = endWord;

    while (currentWord != startWord) {
        wordChain.push_back(currentWord);
        currentWord = predecessors.at(currentWord);
    }

    wordChain.push_back(startWord);
    std::reverse(wordChain.begin(), wordChain.end());

    return wordChain;
}

// Dictionary constructor that reads words from the input stream and creates the dictionary
Dictionary::Dictionary(std::istream& stream) {
    std::string word;
    while (std::getline(stream, word)) {
        if (word.empty())
            continue;

        bool validWord = true;
        for (char c : word) {
            if (!std::islower(c)) {
                validWord = false;
                break;
            }
        }

        if (validWord) {
            words[word.length()].push_back(word);
        }
    }
}

// Create function used by the autograder to create the dictionary
Dictionary* Dictionary::create(std::istream& stream) {
    return new Dictionary(stream);
}

// Function to find a valid chain of words from 'from' to 'to'
std::vector<std::string> Dictionary::hop(const std::string& from, const std::string& to) {
    if (from.length() != to.length()) {
        throw InvalidWord("Words must be of the same length.");
    }

    if (from == to) {
        return { from };
    }

    if (words[from.length()].empty() || words[to.length()].empty()) {
        throw InvalidWord("Invalid word.");
    }

    std::unordered_map<std::string, std::string> predecessors;
    std::vector<std::vector<std::string>> wordMap(from.length() + 1);

    std::queue<std::string> wordQueue;
    wordQueue.push(from);

    wordMap[from.length()].push_back(from);
    predecessors[from] = from;

    while (!wordQueue.empty()) {
        std::string currentWord = wordQueue.front();
        wordQueue.pop();

        if (currentWord == to) {
            return generateWordChain(predecessors, from, to);
        }

        for (const std::string& nextWord : words[currentWord.length()]) {
            if (isOneLetterDifference(currentWord, nextWord) &&
                predecessors.find(nextWord) == predecessors.end()) {
                predecessors[nextWord] = currentWord;
                wordMap[nextWord.length()].push_back(nextWord);
                wordQueue.push(nextWord);
            }
        }
    }

    throw NoChain();
}