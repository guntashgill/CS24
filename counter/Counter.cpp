#include "Counter.h"

Counter::Counter() : size(0) {}

std::size_t Counter::count() const {
    return size;
}

int Counter::total() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i) {
        sum += counts[i];
    }
    return sum;
}

void Counter::inc(const std::string& key, int by) {
    for (std::size_t i = 0; i < size; ++i) {
        if (keys[i] == key) {
            counts[i] += by;
            return;
        }
    }

    if (size < MAX_SIZE) {
        keys[size] = key;
        counts[size] = by;
        ++size;
    }
}

void Counter::dec(const std::string& key, int by) {
    for (std::size_t i = 0; i < size; ++i) {
        if (keys[i] == key) {
            counts[i] -= by;
            if (counts[i] <= 0) {
                --size;
                keys[i] = keys[size];
                counts[i] = counts[size];
            }
            return;
        }
    }
}

void Counter::del(const std::string& key) {
    for (std::size_t i = 0; i < size; ++i) {
        if (keys[i] == key) {
            --size;
            keys[i] = keys[size];
            counts[i] = counts[size];
            return;
        }
    }
}

int Counter::get(const std::string& key) const {
    for (std::size_t i = 0; i < size; ++i) {
        if (keys[i] == key) {
            return counts[i];
        }
    }
    return 0;
}

void Counter::set(const std::string& key, int count) {
    for (std::size_t i = 0; i < size; ++i) {
        if (keys[i] == key) {
        counts[i] = count;
        return;
        }
    }

    if (size < MAX_SIZE) {
        keys[size] = key;
        counts[size] = count;
        ++size;
    }
}
Counter::Iterator Counter::begin() const {
    return Iterator(this, 0);
}

Counter::Iterator Counter::end() const {
    return Iterator(this, size);
}

const std::string& Counter::getFilename() const {
    return filename;
}

void Counter::setFilename(const std::string& filename) {
    this->filename = filename;
}