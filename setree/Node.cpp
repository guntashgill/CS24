
#include "Node.h"

static std::string treeToString(const Node* node) {
    if (node == nullptr) {
        return "-";
    }
    std::string leftSubtreeStr = treeToString(node->left);
    std::string rightSubtreeStr = treeToString(node->right);
    if (leftSubtreeStr == "-" && rightSubtreeStr == "-") {
        return node->value;
    } else {
        return "(" + leftSubtreeStr + " " + node->value + " " + rightSubtreeStr + ")";
    }
}

static Node* treeFromString(const std::string& str, size_t& index) {
    if (index >= str.size() || str[index] == '-') {
        index++;
        return nullptr;
    }
    std::string value = "";
    while (index < str.size() && str[index] != '(' && str[index] != ')' && str[index] != ' ') {
        value += str[index];
        index++;
    }
    Node* node = new Node(value);
    if (index < str.size() && str[index] == '(') {
        index++;
        node->left = treeFromString(str, index);
    }
    if (index < str.size() && str[index] == ' ') {
        index++;
        node->right = treeFromString(str, index);
    }
    return node;
}

std::string Node::toString() const {
    return treeToString(this);
}

Node* Node::fromString(const std::string& str) {
    size_t index = 0;
    return treeFromString(str, index);
}



