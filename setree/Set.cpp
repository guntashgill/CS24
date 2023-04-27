#include "Set.h"
#include <stdexcept>
#include <iostream>
#include <string>

Set::Set() : mRoot(nullptr) {}

Set::Set(const Set& other) {
    mRoot = other.mRoot ? new Node(*other.mRoot) : nullptr;
}

Set::Set(Set&& other) {
    mRoot = other.mRoot;
    other.mRoot = nullptr;
}

Set::~Set() {
    clear();
}

size_t clearHelper(Node* node) {
    if (!node) {
        return 0;
    }
    size_t count = clearHelper(node->left) + clearHelper(node->right) + 1;
    delete node;
    return count;
}

size_t Set::clear() {
    size_t count = clearHelper(mRoot);
    mRoot = nullptr;
    return count;
}

bool Set::contains(const std::string& value) const {
    Node* node = mRoot;
    while (node) {
        int nodeValue = std::atoi(value.c_str());
        if (nodeValue < node->value) {
            node = node->left;
        } else if (nodeValue > node->value) {
            node = node->right;
        } else {
            return true;
        }
    }
    return false;
}

size_t countHelper(Node* node) {
    if (!node) {
        return 0;
    }
    return countHelper(node->left) + countHelper(node->right) + 1;
}

size_t Set::count() const {
    return countHelper(mRoot);
}

size_t Set::insert(const std::string& value) {
    if (!mRoot) {
        mRoot = new Node(std::atoi(value.c_str()));
        return 1;
    }

    Node* parent = nullptr;
    Node* node = mRoot;
    while (node) {
        int nodeValue = std::atoi(value.c_str());
        if (nodeValue < node->value) {
            parent = node;
            node = node->left;
        } else if (nodeValue > node->value) {
            parent = node;
            node = node->right;
        } else {
            return 0;
        }
    }

    if (std::atoi(value.c_str()) < parent->value) {
        parent->left = new Node(std::atoi(value.c_str()));
    } else {
        parent->right = new Node(std::atoi(value.c_str()));
    }

    return 1;
}
void inorder(Node* node, std::vector<int>& result) {
    if (node) {
        inorder(node->left, result);
        result.push_back(node->value);
        inorder(node->right, result);
    }
}

const std::string& Set::lookup(size_t n) const {
    if (!mRoot || n < 1) {
        throw std::out_of_range("Index out of range");
    }

    std::vector<int> values;
    inorder(mRoot, values);

    if (n > values.size()) {
        throw std::out_of_range("Index out of range");
    }

    return std::to_string(values[n-1]);
}


void printHelper(Node* node) {
    if (!node) {
        return;
    }

    printHelper(node->left);
    std::cout << node->value << std::endl;
    printHelper(node->right);
}
void Set::print() const {
    printHelper(mRoot);
}
size_t Set::remove(const std::string& value) {
    if (!mRoot) {
        return 0;
    }

    Node* parent = nullptr;
    Node* node = mRoot;

    while (node) {
        int nodeValue = std::atoi(std::to_string(node->value).c_str());
        int targetValue = std::atoi(value.c_str());
        if (targetValue < nodeValue) {
            parent = node;
            node = node->left;
        } else if (targetValue > nodeValue) {
            parent = node;
            node = node->right;
        } else {
            break;
        }
    }

    if (!node) {
        return 0;
    }

    if (node->left && node->right) {
        Node* successor = node->right;
        parent = node;

        while (successor->left) {
            parent = successor;
            successor = successor->left;
        }

        node->value = successor->value;
        node = successor;
    }

    Node* child = node->left ? node->left : node->right;

    if (!parent) {
        mRoot = child;
    } else if (node == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    delete node;
    return 1;
}
