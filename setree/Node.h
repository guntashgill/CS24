
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <ostream>

struct Node {
    std::string value;
    Node* left;
    Node* right;
    size_t leftSubtreeSize;
    size_t rightSubtreeSize;

    Node(const std::string& value, Node* left = nullptr, Node* right = nullptr)
        : value(value), left(left), right(right), leftSubtreeSize(0), rightSubtreeSize(0) {}


    size_t size() const {
        return leftSubtreeSize + rightSubtreeSize + 1;
    }

void printSubtree() const {
    if (!left && !right) {
        std::cout << value;
        return;
    }
    std::cout << "(";
    if (left) {
        left->printSubtree();
    } else {
        std::cout << "-";
    }
    std::cout << " " << value << " ";
    if (right) {
        right->printSubtree();
    } else {
        std::cout << "-";
    }
    std::cout << ")";
}
Node* copyhelper(Node* node) {}
    std::string toString() const;
    static Node* fromString(const std::string& str);
};

#endif



