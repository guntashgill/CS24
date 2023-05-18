#include "Counter.h"
#include <iostream>

Counter::Counter() : counterSize(0), hashTable(new HashNode*[100]()) {}

Counter::~Counter() {
    for (std::size_t i = 0; i < 100; ++i) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* next = node->next;
            delete node;
            node = next;
        }
    }
    delete[] hashTable;
}

std::size_t Counter::count() const {
    return counterSize;
}

int Counter::total() const {
    int sum = 0;
    for (std::size_t i = 0; i < 100; ++i) {
        HashNode* node = hashTable[i];
        while (node) {
            sum += node->count;
            node = node->next;
        }
    }
    return sum;
}

std::size_t Counter::hash(const std::string& key) const {
    std::size_t hashValue = 0;
    for (char c : key) {
        hashValue += c;
    }
    return hashValue % 100;
}


Counter::HashNode* Counter::findNode(const std::string& key) const {
    std::size_t index = hash(key);
    HashNode* node = hashTable[index];
    while (node) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return nullptr;
}

void Counter::insertNode(const std::string& key, int count) {
    std::size_t index = hash(key);
    HashNode* newNode = new
    HashNode(key, count);
    if (hashTable[index]) {
        newNode->next = hashTable[index];
    }
    hashTable[index] = newNode;
    ++counterSize;
}
void Counter::deleteNode(const std::string& key) {
    std::size_t index = hash(key);
    HashNode* node = hashTable[index];
    HashNode* prevNode = nullptr;
    while (node) {
        if (node->key == key) {
            if (prevNode) {
                prevNode->next = node->next;
            } else {
                hashTable[index] = node->next;
            }
            delete node;
            --counterSize;
            return;
        }
        prevNode = node;
        node = node->next;
    }
}
void Counter::inc(const std::string& key, int by) {
    HashNode* node = findNode(key);
    if (node == nullptr) {
        std::string* newKeys = new std::string[counterSize + 1];
        int* newCounts = new int[counterSize + 1];
        for (std::size_t i = 0; i < counterSize; ++i) {
            newKeys[i] = keys[i];
            newCounts[i] = counts[i];
        }
        newKeys[counterSize] = node->key;
        newCounts[counterSize] = node->count + by;
        ++counterSize;

        delete[] keys;
        delete[] counts;

        keys = newKeys;
        counts = newCounts;
    } else {
        node->count += by;
    }
}
void Counter::dec(const std::string& key, int by) {
    HashNode* node = findNode(key);
    if (node == nullptr) {
        std::string* newKeys = new std::string[counterSize + 1];
        int* newCounts = new int[counterSize + 1];
        for (std::size_t i = 0; i < counterSize; ++i) {
            newKeys[i] = keys[i];
            newCounts[i] = counts[i];
        }
        newKeys[counterSize] = node->key;
        newCounts[counterSize] = -node->count - by;
        ++counterSize;

        delete[] keys;
        delete[] counts;

        keys = newKeys;
        counts = newCounts;
    } else {
        node->count -= by;
    }
}
void Counter::del(const std::string& key) {
    deleteNode(key);

    std::string* newKeys = new std::string[counterSize];
    int* newCounts = new int[counterSize];
    for (std::size_t i = 0, j = 0; i < counterSize; ++i) {
        if (keys[i] != key) {
            newKeys[j] = keys[i];
            newCounts[j] = counts[i];
            ++j;
        }
    }

    delete[] keys;
    delete[] counts;

    keys = newKeys;
    counts = newCounts;
}

int Counter::get(const std::string& key) const {
    HashNode* node = findNode(key);
    if (node != nullptr) {
        return node->count;
    }
}


void Counter::set(const std::string& key, int count) {
    HashNode* node = findNode(key);
    if (node == nullptr) {
        std::string* newKeys = new std::string[counterSize + 1];
        int* newCounts = new int[counterSize + 1];
        for (std::size_t i = 0; i < counterSize; ++i) {
            newKeys[i] = keys[i];
            newCounts[i] = counts[i];
        }
        newKeys[counterSize] = key;
        newCounts[counterSize] = count;
        ++counterSize;

        delete[] keys;
        delete[] counts;

        keys = newKeys;
        counts = newCounts;
    } else {
        node->count = count;
    }
}

Counter::Iterator Counter::begin() const {
    return Iterator(this, 0);
}

Counter::Iterator Counter::end() const {
    return Iterator(this, counterSize);
}

const std::string& Counter::getFilename() const {
    return filename;
}

void Counter::setFilename(const std::string& filename) {
    this->filename = filename;
}
