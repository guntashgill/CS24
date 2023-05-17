#include "Counter.h"

Counter::Counter() : counterSize(0), buckets(nullptr), numBuckets(8) {
  buckets = new Node*[numBuckets]();
}

Counter::~Counter() {
    for (std::size_t i = 0; i < numBuckets; ++i) {
        Node* current = buckets[i];
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] buckets;
}

std::size_t Counter::count() const {
    return counterSize;
}

int Counter::total() const {
    int sum = 0;
    for (std::size_t i = 0; i < numBuckets; ++i) {
        Node* current = buckets[i];
        while (current) {
            sum += current->count;
            current = current->next;
        }
    }
    return sum;
}

std::size_t Counter::hash(const std::string& key) const {
    std::size_t hash = 0;
    for (char c :key) {
        hash = (hash * 31) + c;
    }
    return hash % numBuckets;
}
Counter::Node* Counter::findNode(const std::string& key) const {
    std::size_t index = hash(key);
    Node* current = buckets[index];
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
void Counter::rehash() {
  std::size_t newNumBuckets = numBuckets * 2;
  Node** newBuckets = new Node*[newNumBuckets]();
  for (std::size_t i = 0; i < numBuckets; ++i) {
    Node* current = buckets[i];
    while (current) {
      Node* next = current->next;
      std::size_t newIndex = hash(current->key);
      current->next = newBuckets[newIndex];
      newBuckets[newIndex] = current;
      current = next;
    }
  }
  delete[] buckets;
  buckets = newBuckets;
  numBuckets = newNumBuckets;
}

void Counter::inc(const std::string& key, int by) {
    Node* node = findNode(key);
    if (node) {
        node->count += by;
    } else {
        std::size_t index = hash(key);
        Node* newNode = new Node(key, by, buckets[index]);
        buckets[index] = newNode;
        counterSize++;
        if (counterSize > numBuckets * 2) {
            rehash();
        }
    }
}
void Counter::dec(const std::string& key, int by) {
    Node* node = findNode(key);
    if (node) {
        node->count -= by;
        if (node->count <= 0) {
            del(key);
        }
    }
}
void Counter::del(const std::string& key) {
    std::size_t index = hash(key);
    Node* current = buckets[index];
    Node* prev = nullptr;
    while (current) {
        if (current->key == key) {
            if (prev) {
            prev->next = current->next;
            } else {
            buckets[index] = current->next;
            }
            delete current;
            counterSize--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
int Counter::get(const std::string& key) const {
    Node* node = findNode(key);
    if (node) {
        return node->count;
    }
    return 0;
}

void Counter::set(const std::string& key, int count) {
    Node* node = findNode(key);
    if (node) {
        node->count = count;
    } else {
        inc(key, count);
    }
}
Counter::Iterator Counter::begin() const {
    std::size_t index = 0;
    while (index < numBuckets && !buckets[index]) {
        index++;
    }
    return Iterator(this, index);
}

Counter::Iterator Counter::end() const {
    return Iterator(this, numBuckets);
}