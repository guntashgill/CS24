
#include "Counter.h"

Counter::Iterator::Iterator(const Counter* counter, std::size_t index)
    : counter(counter), index(index) {}

const std::string& Counter::Iterator::key() const {
  return counter->keys[index];
}

int Counter::Iterator::value() const {
  return counter->counts[index];
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

