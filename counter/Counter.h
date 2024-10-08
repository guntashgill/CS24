
#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <string>

class Counter {
public:
  class Iterator {
  private:
    const Counter* counter;
    std::size_t index;

  public:
    Iterator(const Counter* counter, std::size_t index);

    const std::string& key() const;
    int value() const;

    Iterator& operator++();
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
  };

private:
  std::string filename;
  std::size_t counterSize;
  std::string* keys;
  int* counts;
  struct HashNode {
    std::string key;
    int count;
    HashNode* next;

    HashNode(const std::string& key, int count) : key(key), count(count), next(nullptr) {}
  };
  HashNode** hashTable;
  std::size_t hash(const std::string& key) const;
  HashNode* findNode(const std::string& key) const;
  void insertNode(const std::string& key, int count);
  void deleteNode(const std::string& key);

public:
  Counter();
  ~Counter();

  std::size_t count() const;
  int total() const;

  void inc(const std::string& key, int by = 1);
  void dec(const std::string& key, int by = 1);
  void del(const std::string& key);
  int get(const std::string& key) const;
  void set(const std::string& key, int count);

  Iterator begin() const;
  Iterator end() const;
  const std::string& getFilename() const;
  void setFilename(const std::string& filename);
};

#endif