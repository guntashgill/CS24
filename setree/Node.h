
#ifndef NODE_H
#define NODE_H

struct Node {
    std::string value;
    Node* left;
    Node* right;
    size_t leftSubtreeSize;
    size_t rightSubtreeSize;
    Node(const std::string& value)
        : value(value), left(nullptr), right(nullptr), leftSubtreeSize(0), rightSubtreeSize(0){}
    ~Node() {
        delete left;
        delete right;
    }
    size_t size() const {
        return leftSubtreeSize + rightSubtreeSize + 1;
    }
    void printSubtree(bool isLeft, std::string indent) const {
        std::cout << indent;
        if (isLeft) {
            std::cout << "|-";
        } else {
            std::cout << "|_";
        }
        std::cout << value << std::endl;
        if (left) {
            left->printSubtree(true, indent + (isLeft ? "|  " : "   "));
        }
        if (right) {
            right->printSubtree(false, indent + (isLeft ? "   " : "|  "));
        }
    }
};
// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.

#endif