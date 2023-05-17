
#include "Counter.h"

Counter::Counter() : counterSize(0), keys(nullptr), counts(nullptr) {}

Counter::~Counter() {
    delete[] keys;
    delete[] counts;
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

std::size_t Counter::hash(const std::string& key) const {
    std::size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % counterSize;
}

std::size_t Counter::findIndex(const std::string& key) const {
    for (std::size_t i = 0; i < counterSize; ++i) {
        if (keys[i] == key) {
            return i;
        }
    }
    return counterSize;
}
void Counter::rehash() {
    std::size_t newNumBuckets = counterSize * 2;
    std::string* newKeys = new std::string[newNumBuckets];
    int* newCounts = new int[newNumBuckets]();

    for (std::size_t i = 0; i < counterSize; ++i) {
        newKeys[i] = keys[i];
        newCounts[i] = counts[i];
    }

    delete[] keys;
    delete[] counts;

    keys = newKeys;
    counts = newCounts;
    counterSize = newNumBuckets;
}


void Counter::inc(const std::string& key, int by) {
    std::size_t index = findIndex(key);
    if (index == counterSize) {
        std::string* newKeys = new std::string[counterSize + 1];
        int* newCounts = new int[counterSize + 1];
        for (std::size_t i = 0; i < counterSize; ++i) {
            newKeys[i] = keys[i];
            newCounts[i] = counts[i];
        }
        newKeys[counterSize] = key;
        newCounts[counterSize] = by;
        ++counterSize;

        delete[] keys;
        delete[] counts;

        keys = newKeys;
        counts = newCounts;
    } else {
        counts[index] += by;
    }
}

void Counter::dec(const std::string& key, int by) {
    std::size_t index = findIndex(key);
    if (index == counterSize) {
        std::string* newKeys = new std::string[counterSize + 1];
        int* newCounts = new int[counterSize + 1];
        for (std::size_t i = 0; i < counterSize; ++i) {
            newKeys[i] = keys[i];
            newCounts[i] = counts[i];
        }
        newKeys[counterSize] = key;
        newCounts[counterSize] = -by;
        ++counterSize;

        delete[] keys;
        delete[] counts;

        keys = newKeys;
        counts = newCounts;
    } else {
        counts[index] -= by;
    }
}

void Counter::del(const std::string& key) {
    std::size_t index = findIndex(key);
    if (index != counterSize) {
        std::string* newKeys = new std::string[counterSize - 1];
        int* newCounts = new int[counterSize - 1];
        for (std::size_t i = 0, j = 0; i < counterSize; ++i) {
            if (i != index) {
                newKeys[j] = keys[i];
                newCounts[j] = counts[i];
                ++j;
            }
        }
        --counterSize;
        delete[] keys;
        delete[] counts;
        keys = newKeys;
        counts = newCounts;
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
        counts[index] = count;
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