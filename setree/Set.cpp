#include "Set.h"
#include <stdexcept>
#include <iostream>

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
const std::string& Set::lookup(size_t n) const {
    if (!mRoot || n < 1 || n > mRoot->size()) {
        throw std::out_of_range("Index out of range");
    }

    Node* node = mRoot;

    while (node) {
        size_t leftSize = node->left ? node->left->size() : 0;

        if (n <= leftSize) {
            node = node->left;
        } else if (n == leftSize + 1) {
            return node->value;
        } else {
            n -= leftSize + 1;
            node = node->right;
        }
    }

    throw std::out_of_range("Index out of range");
}
void Set::print() const {
    if (!mRoot) {
        return;
    }

    std::cout << mRoot->value << std::endl;
    std::cout << "-";
    if (mRoot->left) {
        mRoot->left->printSubtree(true, "");
    }
    std::cout << "-";
    if (mRoot->right) {
        mRoot->right->printSubtree(false, "");
    }
}
size_t Set::remove(const std::string& value) {
    size_t count = 0;
    Node* curr = mRoot;
    Node* parent = nullptr;
    while (curr != nullptr && curr->value != value) {
        parent = curr;
        if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (curr == nullptr) {
        return count;
    }
    if (curr->left != nullptr && curr->right != nullptr) {
        Node* largest = curr->left;
        Node* largestParent = curr;
        while (largest->right != nullptr) {
            largestParent = largest;
            largest = largest->right;
        }
        curr->value = largest->value;
        curr = largest;
        parent = largestParent;
    }
    Node* child;
    if (curr->left != nullptr) {
        child = curr->left;
    } else {
        child = curr->right;
    }
    if (parent == nullptr) {
        mRoot = child;
    } else if (curr == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    delete curr;
    count++;
    return count;
}