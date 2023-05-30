#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "Dictionary.h"

// Constructor for the Dictionary class
Dictionary::Dictionary(std::istream &stream) {
    std::string word;
    // Read words from the input stream and insert them into an unordered_set
    while (stream >> word) {
        words.insert(word);
    }
}

// Static function to create a new Dictionary object from an input stream
Dictionary *Dictionary::create(std::istream &stream) {
    return new Dictionary(stream);
}

// Function to find a valid chain of words from "from" to "to"
std::vector<std::string> Dictionary::hop(const std::string &from, const std::string &to) {
    // Check if "from" and "to" are valid words
    if (words.find(from) == words.end() || words.find(to) == words.end()) {
        throw InvalidWord();
    }

    // Initialize a set of visited words and a queue of partial paths
    std::unordered_set<std::string> visited;
    std::queue<std::vector<std::string>> q;
    q.push({from});
    visited.insert(from);

    // Perform a BFS algorithm to find the shortest path from "from" to "to"
    while (!q.empty()) {
        std::vector<std::string> path = q.front();
        q.pop();

        // If the last word in the path is "to", return the path
        if (path.back() == to) {
            return path;
        }

        // Generate all possible neighbors of the last word in the path
        std::string current = path.back();
        for (size_t i = 0; i < current.size(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                std::string next = current;
                next[i] = c;

                // If the neighbor is a valid word and has not been visited, add it to the path and the queue
                if (words.find(next) != words.end() && visited.find(next) == visited.end()) {
                    std::vector<std::string> newPath(path);
                    newPath.push_back(next);
                    q.push(newPath);
                    visited.insert(next);
                }
            }
        }
    }

    // If no valid chain exists, throw a NoChain exception
    throw NoChain();
}


