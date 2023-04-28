#ifndef NODE_H
#define NODE_H

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r) {}
};

Node* buildTree(int v[], int size, int index = 0) {
    if (index >= size) return nullptr;
    Node* root = new Node(v[index]);
    root->left = buildTree(v, size, 2*index+1);
    root->right = buildTree(v, size, 2*index+2);
    return root;
}

void printTree(Node* root) {
    if (!root) return;
    std::cout << "(";
    printTree(root->left);
    std::cout << root->value;
    printTree(root->right);
    std::cout << ")";
}

#endif



