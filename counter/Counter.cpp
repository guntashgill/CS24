#include "Counter.h"

Counter::Counter() {}

std::size_t Counter::count() const {
  return counts.size();
}

int Counter::total() const {
  int sum = 0;
  for (const auto& pair : counts) {
    sum += pair.second;
  }
  return sum;
}

void Counter::inc(const std::string& key, int by) {
  counts[key] += by;
}

void Counter::dec(const std::string& key, int by) {
  counts[key] -= by;
}

void Counter::del(const std::string& key) {
  counts.erase(key);
}

int Counter::get(const std::string& key) const {
  auto it = counts.find(key);
  if (it != counts.end()) {
    return it->second;
  }
  return 0;
}

void Counter::set(const std::string& key, int count) {
  counts[key] = count;
}

Counter::Iterator Counter::begin() const {
  return Iterator(this, 0);
}

Counter::Iterator Counter::end() const {
  return Iterator(this, counts.size());
}

const std::string& Counter::getFilename() const {
  return filename;
}

void Counter::setFilename(const std::string& filename) {
  this->filename = filename;
}