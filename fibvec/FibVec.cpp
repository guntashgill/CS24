#include "FibVec.h"

// This provides exception types:
#include <stdexcept>


FibVec* create_fibvec() {
  // Used by the autograder to make a new FibVec.
  // You shouldn't need to change this.
  return new FibVec();
}

// FibVec::FibVec() {
//   _capacity = 1;
//   count_ = 0;
//   data = new int[_capacity];
// }

// FibVec::~FibVec() {
//   delete[] data;
// }

// size_t FibVec::capacity() const {
//   return _capacity;
// }
// size_t FibVec::count() const {
//   return count_;
// }
// void FibVec::insert(int value, size_t index) {
//   if (index> _capacity) {
//     throw std::out_of_range("Invalid index");
//   }
//   if (count_ == _capacity) {
//     resize(_capacity +1);
// }
// for (size_t i = count_; i > index; i --) {
//   data[i] = data[i-1];
// }
// data[index] = value;
// count_++;
// }

// int FibVec::remove(size_t index) {
//     if (index >= count_) {
//         throw std::out_of_range("Invalid index");
//     }

//     int value = data[index];

//     for (size_t i = index; i < count_ - 1; i++) {
//         data[i] = data[i + 1];
//     }

//     count_--;

//     if (count_ <= _capacity / 2 && _capacity > 1) {
// resize(_capacity - 1);
// }
// return value;
// }

// void FibVec::resize(size_t new_capacity) {
// if (new_capacity == _capacity) {
// return; 
// }
// size_t fib = 0;
// size_t fib_minus_1 = 0;
// size_t fib_minus_2 = 1;
// while (fib < new_capacity) {
//     size_t temp = fib;
//     fib = fib_minus_1 + fib_minus_2;
//     fib_minus_2 = fib_minus_1;
//     fib_minus_1 = temp;
// }

// int* new_data = new int[fib];

// for (size_t i = 0; i < count_; i++) {
//     new_data[i] = data[i];
// }

// delete[] data;
// data = new_data;
// _capacity = fib;

// }


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
  for (size_t i = 0; i < count_; i++){
    new_data = data;
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
    size_t new_capacity = fib(3);
    while (new_capacity <= count_) {
      new_capacity = fib(new_capacity +1);
    }
    resize(new_capacity);
  }
  for (size_t i = count_; i > index; i --) {
    data[i] = data[i-1];
  }
  data[index] = value;
  count_++;
}


int FibVec::lookup(size_t index) const{
  if (index >= count_) {
    throw std::out_of_range("index out of range");
  }
  return data[index];
}

int FibVec::pop() {
  if(count_ == 0) {
    throw std::underflow_error("vector is empty");
  }
  count_--;
  if(count_ <= fib(_capacity-3)){
    size_t new_capacity = fib(_capacity-2);
    resize(new_capacity);
  }
  return data[count_];
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

    if (count_ <= _capacity / 2 && _capacity > 1) {
resize(_capacity - 1);
}
return value;
}

void FibVec::push(int value){
  insert(value, count_);
}

// FibVec Function Implementations
