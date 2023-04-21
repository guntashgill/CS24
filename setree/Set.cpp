#include "Set.h"
#include <stdexcept>

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
        if (value < node->value) {
            node = node->left;
        } else if (value > node->value) {
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
        mRoot = new Node(value);
        return 1;
    }

    Node* parent = nullptr;
    Node* node = mRoot;
    while (node) {
        if (value < node->value) {
            parent = node;
            node = node->left;
        } else if (value > node->value) {
            parent = node;
            node = node->right;
        } else {
            return 0;
        }
    }

    if (value < parent->value) {
        parent->left = new Node(value);
    } else {
        parent->right = new Node(value);
    }

    return 1;
}


