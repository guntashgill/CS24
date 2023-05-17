#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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
  std::unordered_map<std::string, int> counts;

public:
  Counter();

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




