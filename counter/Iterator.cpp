
#include "Counter.h"

Counter::Iterator::Iterator(const Counter* counter, std::size_t index)
    : counter(counter), index(index) {}

const std::string& Counter::Iterator::key() const {
  auto it = counter->counts.begin();
  std::advance(it, index);
  return it->first;
}

int Counter::Iterator::value() const {
  auto it = counter->counts.begin();
  std::advance(it, index);
  return it->second;
}

Counter::Iterator& Counter::Iterator::operator++() {
  ++index;
  return *this;
}

bool Counter::Iterator::operator==(const Iterator& other) const {
  return counter == other.counter && index == other.index;
}

bool Counter::Iterator::operator!=(const Iterator& other) const {
  return !(*this == other);
}

