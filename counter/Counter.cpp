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
    if (node) {
        node->count += by;
    } else {
        insertNode(key, by);
    }
}
void Counter::dec(const std::string& key, int by) {
    HashNode* node = findNode(key);
    if (node) {
        node->count -= by;
    } else {
        insertNode(key, -by);
    }
}
void Counter::del(const std::string& key) {
    deleteNode(key);
}

int Counter::get(const std::string& key) const {
    HashNode* node = findNode(key);
    if (node) {
        return node->count;
    }
    return 0;
}

void Counter::set(const std::string& key, int count) {
    HashNode* node = findNode(key);
    if (node) {
        node->count = count;
    } else {
        insertNode(key, count);
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
