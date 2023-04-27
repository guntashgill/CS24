#include "Node.h"
#include "Set.h"

size_t clearHelper(Node* node) {
    if (!node) {
        return 0;
    }
    size_t count = clearHelper(node->left) + clearHelper(node->right) + 1;
    delete node;
    return count;
}

size_t countHelper(Node* node) {
    if (!node) {
        return 0;
    }
    return countHelper(node->left) + countHelper(node->right) + 1;
}







