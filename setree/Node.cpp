#include "Node.h"

std::string Node::to_tree_notation() {
    if (this == nullptr) {
        return "-";
    }
    else if (is_leaf()) {
        return std::to_string(data);
    }
    else {
        std::string left_subtree = left->to_tree_notation();
        std::string right_subtree = right->to_tree_notation();
        return "(" + left_subtree + " " + std::to_string(data) + " " + right_subtree + ")";
    }
}

void Node::sorted_insert(int_fast32_t newData) {
    if (data == '\0') {
        data = newData;
    }
    else if (newData < data) {
        if (left == nullptr) {
            left = new Node(newData);
        }
        else {
            left->sorted_insert(newData);
        }
    }
    else {
        if (right == nullptr) {
            right = new Node(newData);
        }
        else {
            right->sorted_insert(newData);
        }
    }
}



