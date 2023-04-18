#include "FibVec.h"

// This provides exception types:
#include <stdexcept>


FibVec* create_fibvec() {
  // Used by the autograder to make a new FibVec.
  // You shouldn't need to change this.
  return new FibVec();
}

static size_t fib(size_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n-1) + fib(n-2);
    }
}
FibVec::FibVec() {
    data = new int[1];
    _capacity = 1;
    count_ = 0;
    store_ = 2;
}
FibVec::~FibVec() {
  delete[] data;
}
size_t FibVec::capacity() const {
  return _capacity;
}
size_t FibVec::count() const{
  return count_;
}
void FibVec::resize(size_t new_capacity){
  int* new_data = new int[new_capacity];
try {
  for (size_t i = 0; i < count_; i++){
    new_data[i] = data[i];
  }
} catch (...) {
  delete[] new_data;
  throw;
}
  for (size_t i = 0; i < count_; i++){
    new_data[i] = data[i];
  }
  delete[] data;
  data = new_data;
  _capacity = new_capacity;
}

void FibVec::insert(int value, size_t index){
  if (index >count_) {
    throw std::out_of_range("index out of range");
  }
  if (count_ == _capacity) {
    store_++; 
    size_t new_capacity = fib(store_);
    while (new_capacity <= count_) {
      new_capacity = fib(new_capacity +1);
    }
    resize(new_capacity);
  }
  for (size_t i = count_; i > index; i--) {
    data[i] = data[i-1];
  }
  data[index] = value;
  count_++;
}



int FibVec::lookup(size_t index) const{
  if (index >= count_ || count_ == 0) {
    throw std::out_of_range("index out of range");
  }
  return data[index];
}


// int FibVec::pop() {
// if (count_ == 0) {
//   throw std::underflow_error("Underflow.");
// } else if (count_ == 1) {
//   int value = data[0];
//   count_ = 0;
//   resize(1);
//   return value;
// }
//   int value = data[count_ - 1];
//   count_--;

// if (count_ == 0) {
//   resize(1);
// } else {
//   bool is_fib = false;
//   int fib_idx = 2; 
//   while (fib(fib_idx) <= count_+1) {
//     if (fib(fib_idx) == count_) {
//       is_fib = true;
//       break;
//     }
//     fib_idx++;
//   }

//   if (!is_fib) {
//     size_t new_capacity = fib(fib_idx - 1);
//     resize(new_capacity);
//   }
// }

//   return value; 
// }



int FibVec::pop() {
if (count_ == 0) {
  throw std::underflow_error("Underflow.");
} else if (count_ == 1) {
  int value = data[0];
  count_ = 0;
  resize(1);
  return value;
}
  int value = data[count_ - 1];
  count_--;

  if (count_ == 0) {
    resize(1);
  } else {
    int fib_idx = 0; 
    while (fib(fib_idx) < count_) {
      fib_idx++;
    }

    resize(fib(fib_idx+1));
  }

  return value; 
}



int FibVec::remove(size_t index) {
    if (index >= count_) {
        throw std::out_of_range("Invalid index");
    }

    int value = data[index];

    for (size_t i = index; i < count_ - 1; i++) {
        data[i] = data[i + 1];
    }

    count_--;

    if (count_ <= _capacity / 2 && _capacity > 2 && count_ <= fib(store_ - 1)) {
        resize(_capacity - 1);
    }
    return value;
}

void FibVec::push(int value){
  insert(value, count_);
}

// FibVec Function Implementations