#include "Counter.h"

Counter::Counter() : counterSize(0), keys(nullptr), counts(nullptr), hashTable(nullptr) {}

Counter::~Counter() {
    delete[] keys;
    delete[] counts;
    delete[] hashTable;
}

std::size_t Counter::count() const {
    return counterSize;
}

int Counter::total() const {
    int sum = 0;
    for (std::size_t i = 0; i < counterSize; ++i) {
        sum += counts[i];
    }
    return sum;
}

std::size_t Counter::calculateHash(const std::string& key) const {
    std::size_t hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return hash;
}

std::size_t Counter::findIndex(const std::string& key) const {
    std::size_t hash = calculateHash(key);
    std::size_t index = hash % counterSize;
    while (index != counterSize && keys[index] != key) {
        index = (index + 1) % counterSize;
    }
    return index;
}

void Counter::inc(const std::string& key, int by) {
    std::size_t index = findIndex(key);
    if (index == counterSize) {
        std::size_t hash = calculateHash(key);
        index = hash % counterSize;
        while (index != counterSize && !keys[index].empty()) {
            index = (index + 1) % counterSize;
        }

        if (index == counterSize) {
            std::size_t newSize = counterSize == 0 ? 1 : counterSize * 2;
            std::string* newKeys = new std::string[newSize];
            int* newCounts = new int[newSize];
            std::size_t* newHashTable = new std::size_t[newSize];

            for (std::size_t i = 0; i < newSize; ++i) {
                newKeys[i] = "";
                newCounts[i] = 0;
                newHashTable[i] = counterSize;
            }
            for (std::size_t i = 0; i < counterSize; ++i) {
                std::size_t newIndex = calculateHash(keys[i]) % newSize;
                while (newKeys[newIndex] != "") {
                    newIndex = (newIndex + 1) % newSize;
                }
                newKeys[newIndex] = keys[i];
                newCounts[newIndex] = counts[i];
                newHashTable[newIndex] = newIndex;
            }
            delete[] keys;
            delete[] counts;
            delete[] hashTable;

            keys = newKeys;
            counts = newCounts;
            hashTable = newHashTable;

            counterSize = newSize;

            index = hash % counterSize;
            while (index != counterSize && !keys[index].empty()) {
                index = (index + 1) % counterSize;
            }
        }
        keys[index] = key;
        counts[index] = by;
        hashTable[index] = index;
    } else {
        counts[index] += by;
    }
}
void Counter::dec(const std::string& key, int by) {
    std::size_t index = findIndex(key);
    if (index != counterSize) {
        counts[index] -= by;
    }
}
void Counter::del(const std::string& key) {
    std::size_t index = findIndex(key);
    if (index != counterSize) {
        std::size_t emptyIndex = index;
        std::size_t nextIndex = (index + 1) % counterSize;
        while (!keys[nextIndex].empty()) {
            std::size_t newIndex = calculateHash(keys[nextIndex]) % counterSize;
            if (newIndex != nextIndex) {
                keys[emptyIndex] = keys[nextIndex];
                counts[emptyIndex] = counts[nextIndex];
                hashTable[emptyIndex] = emptyIndex;
                keys[nextIndex] = "";
                counts[nextIndex] = 0;
                emptyIndex = nextIndex;
            }
            nextIndex = (nextIndex + 1) % counterSize;
        }
        keys[emptyIndex] = "";
        counts[emptyIndex] = 0;
        hashTable[emptyIndex] = counterSize;
    }
}
int Counter::get(const std::string& key) const {
    std::size_t index = findIndex(key);
    if (index != counterSize) {
        return counts[index];
    }
    return 0;
}
void Counter::set(const std::string& key, int count) {
    std::size_t index = findIndex(key);
    if (index == counterSize) {
        inc(key, count);
    } else {
        counts[index] = count;
    }
}
Counter::Iterator Counter::begin() const {
    std::size_t index = 0;
    while (index < counterSize && keys[index].empty()) {
        ++index;
    }
    return Iterator(this, index);
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