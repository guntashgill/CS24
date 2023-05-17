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
  struct Node {
    std::string key;
    int count;
    Node* next;

    Node(const std::string& key, int count, Node* next = nullptr)
      : key(key), count(count), next(next) {}
  };

  std::size_t counterSize;
  Node** buckets;
  std::size_t numBuckets;

  std::size_t hash(const std::string& key) const;
  Node* findNode(const std::string& key) const;
  void rehash();

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
};

#endif


