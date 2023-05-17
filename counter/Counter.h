#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <iostream>
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
  static const std::size_t MAX_SIZE = 4096;

  std::string filename;
  std::string keys[MAX_SIZE];
  int counts[MAX_SIZE];
  std::size_t size;

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





