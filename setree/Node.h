#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r) {}
};

Node* buildTreeHelper(const std::vector<int>& v, int& i) {
    if (i >= v.size() || v[i] == -1) {
        i++;
        return nullptr;
    }
    Node* root = new Node(v[i]);
    i++;
    root->left = buildTreeHelper(v, i);
    root->right = buildTreeHelper(v, i);
    return root;
}

Node* buildTree(std::vector<int>& v) {
    int i = 0;
    return buildTreeHelper(v, i);
}

void printTreeHelper(Node* root) {
    if (root == nullptr) {
        std::cout << "- ";
        return;
    }
    std::cout << root->value << " ";
    printTreeHelper(root->left);
    printTreeHelper(root->right);
}

void printTree(Node* root) {
    printTreeHelper(root);
    std::cout << std::endl;
}

#endif


