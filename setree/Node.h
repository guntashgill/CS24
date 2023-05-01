
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
        int valueLength = value.length();
        std::cout << "(";
        if (left) {
            left->printSubtree();
            std::cout << " ";
        }
        std::cout << value;
        if (right) {
            std::cout << " ";
            right->printSubtree();
        }
        std::cout << ")";
        int totalLength = 2 + valueLength;
        if (left) {
            totalLength += 1;
        }
        if (right) {
            totalLength += 1;
        }
    }

    std::string toString() const;
    static Node* fromString(const std::string& str);
};

#endif



