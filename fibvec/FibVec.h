#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec {  

  // Member Variables

  // Helper Functions

public:
  FibVec();
  ~FibVec();
  //returns the capacity
  size_t capacity() const; 
  //returns the #
  size_t count() const;
  //inserts a value
  void insert(int value, size_t index);
  //returns value at given index
  int lookup(size_t index) const;
  //removes and retuns value
  int pop();
  //inserts value at the end of the vector
  void push(int value);
  //removes and returns value
  int remove(size_t index);

private:
  int* data;
  size_t _capacity;
  size_t count_;
  size_t store_;
  void resize(size_t new_capacity);



// Constructor and Destructor

  // Member Functions

};

// Used by the autograder:
FibVec* create_fibvec();

#endif
