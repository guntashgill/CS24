#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <ostream>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r) {}
};

Node* buildTree(vector<int>& v) {
    if (v.empty()) return nullptr;
    queue<Node*> q;
    Node* root = new Node(v[0]);
    q.push(root);
    int i = 1;
    while (!q.empty() && i < v.size()) {
        Node* curr = q.front();
        q.pop();
        if (v[i] != '-') {
            curr->left = new Node(v[i]);
            q.push(curr->left);
        }
        i++;
        if (i < v.size() && v[i] != '-') {
            curr->right = new Node(v[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

void printTree(Node* root) {
    if (!root) return;
    cout << "(";
    printTree(root->left);
    cout << root->value;
    printTree(root->right);
    cout << ")";
}
#endif

