#ifndef NODE_H
#define NODE_H

struct Node {
    std::string value;
    Node* left;
    Node* right;

    Node(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};
// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.

#endif
